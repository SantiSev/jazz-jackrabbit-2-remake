#include "match.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <memory>
#include <string>
#include <utility>


Match::Match(const uint16_t& map_selected, size_t required_players_setting,
             Queue<std::shared_ptr<Message>>& lobby_queue, ClientMonitor& monitor,
             const std::shared_ptr<engine::ResourcePool>& resource_pool):
        online(true),
        lobby_queue(lobby_queue),
        message_handler(*this),
        players({}),
        enemies({}),
        bullets({}),
        items({}),
        max_players(required_players_setting),
        client_monitor(monitor),
        map(map_selected),
        collision_manager(nullptr),
        resource_pool(resource_pool),
        match_queue(Queue<std::shared_ptr<Message>>()) {
    load_environment();
    load_spawn_points();
    load_items();
    initiate_enemies({character_t::MAD_HATTER, character_t::LIZARD_GOON});
}

void Match::run() {
    try {
        auto startTime = std::chrono::steady_clock::now();
        auto runTime = startTime;

        const double FPSMAX = 1000.0 / 60.0;

        while (!match_has_ended && online) {
            auto frameStart = std::chrono::steady_clock::now();
            std::shared_ptr<Message> message;

            size_t events = 0;
            while (match_queue.try_pop(message) && events < MAX_EVENTS_PER_LOOP) {
                events++;
                if (message) {
                    message->run(message_handler);
                }
            }

            collision_manager->update();
            collision_manager->remove_inactive_bodies();

            respawn_enemies();
            respawn_players();
            respawn_items();

#ifdef LOG_VERBOSE
            for (auto& enemy: enemies) {
                enemy->print_info();
            }

            for (auto& player: players) {
                player.second->print_info();
            }
#endif

            countdown_match(runTime, frameStart);

            auto snapshot = create_actual_snapshot();
            auto snapshot_message = std::make_shared<SendGameStateMessage>(snapshot);
            client_monitor.broadcastClients(snapshot_message);

            auto frameEnd = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> delta = frameEnd - frameStart;

            if (delta.count() < FPSMAX) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(static_cast<int>(FPSMAX - delta.count())));
            }
            startTime = frameStart;
        }
        send_end_message_to_players();
        lobby_queue.push(std::make_shared<SendFinishMatchMessage>());
        while (online) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

//-------------------- Gameloop Methods ----------------------


void Match::countdown_match(std::chrono::time_point<std::chrono::steady_clock>& runTime,
                            const std::chrono::time_point<std::chrono::steady_clock>& endTime) {
    if (match_time != 0) {
        if (std::chrono::duration_cast<std::chrono::seconds>(endTime - runTime).count() >= 1) {
            match_time--;
            runTime = endTime;
            // size_t minutes = match_time / 60;
            // size_t seconds = match_time % 60;
            // std::cout << "Time Remaining: " << std::setw(2) << std::setfill('0') << minutes <<
            // ":" << std::setw(2) << std::setfill('0') << seconds << std::endl;
        }
    } else {
        if (!match_has_ended) {
            match_has_ended = true;
            online = false;
        }
    }
}

void Match::run_command(const CommandDTO& dto) {
    std::shared_ptr<Player> player = get_player(dto.id_player);
    if (player) {
        player->execute_command(dto.command);
    }
}

void Match::respawn_players() {
    for (auto& pair: players) {
        auto& player = pair.second;
        if (player->try_revive()) {

            bool can_be_placed = false;
            engine::Vector2D new_position = get_random_spawn_point(player_spawn_points);
            while (!can_be_placed) {
                std::cout << "Trying to respawn player at " << new_position.x << " "
                          << new_position.y << std::endl;
                can_be_placed = collision_manager->can_be_placed(player, new_position);
                if (!can_be_placed) {
                    new_position = get_random_spawn_point(player_spawn_points);
                }
            }
            std::cout << "Player respawned at " << new_position.x << " " << new_position.y
                      << std::endl;
            player->revive(get_random_spawn_point(player_spawn_points));
            collision_manager->track_dynamic_body(player);
        }
    }
}
void Match::respawn_enemies() {
    for (auto& enemy: enemies) {
        if (enemy->try_revive()) {
            enemy->revive(enemy.get()->spawn_position);
            collision_manager->track_dynamic_body(enemy);
        }
    }
}

void Match::respawn_items() {
    for (auto& item: items) {
        if (item->try_respawn()) {
            item->respawn(item.get()->position);
            collision_manager->track_dynamic_body(item);
        }
    }
}


engine::Vector2D Match::get_random_spawn_point(std::vector<engine::Vector2D> const& spawnpoints) {
    if (spawnpoints.empty()) {
        throw std::runtime_error("No spawn points found in map.");
    }
    int i = rand() % player_spawn_points.size();
    return player_spawn_points[i];
}

void Match::run_cheat_command(const CheatCommandDTO& dto) {

    if (dto.command == CHEAT_KILL_ALL) {
        kill_all_cheat();
    } else if (dto.command == CHEAT_REVIVE) {
        std::shared_ptr<Player> player = get_player(dto.id_player);
        if (player && player->is_dead()) {
            player->revive(get_random_spawn_point(player_spawn_points));
            collision_manager->track_dynamic_body(player);
        }
    } else {
        std::shared_ptr<Player> player = get_player(dto.id_player);
        if (player) {
            player->activate_cheat_command(dto.command);
        }
    }
}

void Match::kill_all_cheat() {
    for (auto& enemy: enemies) {
        enemy->take_damage(9999);
    }
    for (auto& player: players) {
        player.second->take_damage(9999);
    }
}

//-------------------- Conection Methods -----------------

void Match::add_player_to_game(const AddPlayerDTO& dto) {
    engine::Vector2D pos = get_random_spawn_point(player_spawn_points);

    auto player_resources_ptr =
            resource_pool->get_yaml(map_character_enum_to_string.at(dto.player_character));

    if (!player_resources_ptr || player_resources_ptr->IsNull()) {
        std::cerr << "Error loading yaml file" << std::endl;
        exit(1);
    }

    int player_width = (*player_resources_ptr)["body_width"].as<int>();
    int player_height = (*player_resources_ptr)["body_height"].as<int>();
    int shooting_height = (*player_resources_ptr)["weapon_y"].as<int>();

    switch (dto.player_character) {
        case JAZZ_CHARACTER: {

            auto jazz_player = std::make_shared<Jazz>(
                    dto.id_client, dto.name, pos.x, pos.y, player_width, player_height,
                    shooting_height, *collision_manager, resource_pool->get_config());
            collision_manager->track_dynamic_body(jazz_player);
            players[dto.id_client] = jazz_player;
            break;
        }
        case SPAZ_CHARACTER: {

            auto spaz_player = std::make_shared<Spaz>(
                    dto.id_client, dto.name, pos.x, pos.y, player_width, player_height,
                    shooting_height, *collision_manager, resource_pool->get_config());
            collision_manager->track_dynamic_body(spaz_player);
            players[dto.id_client] = spaz_player;
            break;
        }
        case LORI_CHARACTER: {

            auto lori_player = std::make_shared<Lori>(
                    dto.id_client, dto.name, pos.x, pos.y, player_width, player_height,
                    shooting_height, *collision_manager, resource_pool->get_config());
            collision_manager->track_dynamic_body(lori_player);
            players[dto.id_client] = lori_player;
            break;
        }
        default:
            std::cerr << "Invalid character" << std::endl;
            break;
    }


#ifdef LOG_VERBOSE
    std::cout << "Player connected: " << dto.id_client << "is playing as "
              << map_character_enum_to_string.at(dto.player_character) << std::endl;
#endif
}

void Match::send_end_message_to_players() {
    auto game_ended_message = std::make_shared<SendFinishMatchMessage>();
    client_monitor.broadcastClients(game_ended_message);

    //        auto close_connection_message =
    //        std::make_shared<CloseConnectionMessage>(CloseConnectionDTO());
    //        client_monitor.broadcastClients(close_connection_message);
}

bool Match::has_match_ended() const { return match_has_ended; }

void Match::stop() {
    online = false;
//    send_end_message_to_players();
#ifdef LOG_VERBOSE
    std::cout << "stopping match " << std::endl;
#endif
    players.clear();
    client_monitor.remove_all_queues();
#ifdef LOG_VERBOSE
    std::cout << "clients cleared in match" << std::endl;
#endif
}

GameStateDTO Match::create_actual_snapshot() {
    GameStateDTO game_state{};
    memset(&game_state, 0, sizeof(game_state));
    game_state.seconds = (uint16_t)match_time;
    game_state.num_players = players.size();
    size_t i = 0;
    for (auto player = players.begin(); player != players.end(); ++player) {
        game_state.players[i].id = player->second->get_id();
        snprintf(game_state.players[i].name, sizeof(game_state.players[i].name), "%s",
                 player->second->get_name().c_str());
        game_state.players[i].health = (uint16_t)player->second->get_health();
        game_state.players[i].points = (uint16_t)player->second->get_points();
        game_state.players[i].character = player->second->get_character();
        game_state.players[i].state = player->second->get_state();
        game_state.players[i].x_pos = (uint16_t)player->second->position.x;
        game_state.players[i].y_pos = (uint16_t)player->second->position.y;
        for (size_t j = 0; j < NUM_OF_WEAPONS; ++j) {
            game_state.players[i].weapons[j].ammo =
                    (uint16_t)player->second->get_weapon(j)->get_ammo();
            game_state.players[i].weapons[j].is_empty =
                    player->second->get_weapon(j)->get_ammo() == 0 ? (uint8_t)1 : (uint8_t)0;
            game_state.players[i].weapons[j].weapon_name =
                    (uint8_t)player->second->get_weapon(j)->get_weapon_id();
        }
        game_state.players[i].selected_weapon =
                (uint8_t)player->second->get_selected_weapon()->get_weapon_id();
        ++i;
    }

    game_state.num_enemies = 0;
    for (const auto& enemy: enemies) {
        if (!enemy->is_dead()) {
            auto& enemy_state = game_state.enemies[game_state.num_enemies];
            enemy_state.id = enemy->get_id();
            enemy_state.state = enemy->get_state();
            enemy_state.character = enemy->get_character();
            enemy_state.x_pos = (uint16_t)enemy->position.x;
            enemy_state.y_pos = (uint16_t)enemy->position.y;
            game_state.num_enemies++;
        }
    }

    game_state.num_bullets = 0;
    collision_manager->iterateDynamicBodies(
            [&game_state](const std::shared_ptr<engine::DynamicBody>& body) {
                auto bullet = std::dynamic_pointer_cast<Bullet>(body);

                if (bullet) {

                    game_state.bullets[game_state.num_bullets].id = bullet->get_id();
                    game_state.bullets[game_state.num_bullets].direction = bullet->get_direction();
                    game_state.bullets[game_state.num_bullets].bullet_type = bullet->get_type();
                    game_state.bullets[game_state.num_bullets].x_pos = (uint16_t)bullet->position.x;
                    game_state.bullets[game_state.num_bullets].y_pos = (uint16_t)bullet->position.y;
                    game_state.num_bullets++;
                }
            });

    game_state.num_items = 0;
    for (const auto& items: items) {
        if (!items->is_collected()) {
            auto& item_state = game_state.items[game_state.num_items];
            item_state.id = items->get_id();
            item_state.type = items->get_item_type();
            item_state.x_pos = items->position.x;
            item_state.y_pos = items->position.y;
            game_state.num_items++;
        }
    }

    return game_state;
}

//-------------------- Initialization Methods -----------------


void Match::load_environment() {
    auto yaml_maps = *resource_pool->get_yaml(MAPS_FILE);
    auto yaml_path = yaml_maps["maps"][map]["yaml"].as<std::string>();
    resource_pool->load_yaml(yaml_path);
    auto yaml = *resource_pool->get_yaml(yaml_path);

    if (yaml.IsNull()) {
        throw std::runtime_error("Error loading yaml file");
    }
    int grid_width = yaml["map_width"].as<int>();
    int grid_height = yaml["map_height"].as<int>();

    if (grid_width <= 0 || grid_height <= 0) {
        throw std::runtime_error("Invalid map size");
    }

    collision_manager = std::make_unique<engine::CollisionManager>(grid_width, grid_height);

    for (auto obj: yaml["objects"]) {

        bool collision = obj["collision"].as<bool>();

        if (collision) {
            auto d_rect_list_yaml = obj["d_rect_list"];
            for (auto d_rect_obj: d_rect_list_yaml) {
                auto d_rect_yaml = d_rect_obj["d_rect"];

                auto repeat_h = d_rect_yaml["repeat_h"].as<int>();
                auto repeat_v = d_rect_yaml["repeat_v"].as<int>();

                auto x = d_rect_yaml["x"].as<int>();
                auto y = d_rect_yaml["y"].as<int>();
                auto w = d_rect_yaml["w"].as<int>();
                auto h = d_rect_yaml["h"].as<int>();

                // create horizontal boxplatofrm shared pointer
                auto new_h_box = std::make_shared<BoxPlatform>(x, y, w * repeat_h, h);
                collision_manager->add_object(new_h_box);

                // create vertical boxplatofrm shared pointer (y + h to avoid overlapping with
                // horizontal box)
                auto new_v_box = std::make_shared<BoxPlatform>(x, y + h, w, h * repeat_v);
                collision_manager->add_object(new_v_box);
            }
        }
    }
    collision_manager->prepare_map();

#ifdef LOG
    std::cout << "Map loaded!" << std::endl;
#endif
}

void Match::load_items() {
    auto items_yaml = *resource_pool->get_yaml(ITEMS_FILE);
    int item_width = items_yaml["body_width"].as<int>();
    int item_height = items_yaml["body_height"].as<int>();

    if (items_yaml.IsNull()) {
        std::cerr << "Error loading yaml file" << std::endl;
        exit(1);
    }

    int i = 0;
    if (item_spawn_points.empty()) {
        throw std::runtime_error("No item spawn points found in map.");
    }

    for (auto& spawn_point: item_spawn_points) {
        item_t current_item_type = static_cast<item_t>(i % ITEM_AMOUNTS);
        uint16_t id = static_cast<uint16_t>(i);

        switch (current_item_type) {
            case BULLET_ONE_ITEM: {
                auto bullet_one_item = std::make_shared<AmmoGunOne>(
                        id, spawn_point.x, spawn_point.y, item_width, item_height);
                collision_manager->track_dynamic_body(bullet_one_item);
                items.emplace_back(bullet_one_item);
                break;
            }
            case BULLET_TWO_ITEM: {
                auto bullet_two_item = std::make_shared<AmmoGunTwo>(
                        id, spawn_point.x, spawn_point.y, item_width, item_height);
                collision_manager->track_dynamic_body(bullet_two_item);
                items.emplace_back(bullet_two_item);
                break;
            }
            case BULLET_THREE_ITEM: {
                auto bullet_three_item = std::make_shared<AmmoGunThree>(
                        id, spawn_point.x, spawn_point.y, item_width, item_height);
                collision_manager->track_dynamic_body(bullet_three_item);
                items.emplace_back(bullet_three_item);
                break;
            }
            case CARROT: {
                auto carrot = std::make_shared<Carrot>(id, spawn_point.x, spawn_point.y, item_width,
                                                       item_height);
                collision_manager->track_dynamic_body(carrot);
                items.emplace_back(carrot);
                break;
            }
            case MEAT: {
                auto meat = std::make_shared<Meat>(id, spawn_point.x, spawn_point.y, item_width,
                                                   item_height);
                collision_manager->track_dynamic_body(meat);
                items.emplace_back(meat);
                break;
            }
            case COIN: {
                auto coin = std::make_shared<Coin>(id, spawn_point.x, spawn_point.y, item_width,
                                                   item_height);
                collision_manager->track_dynamic_body(coin);
                items.emplace_back(coin);
                break;
            }
            default:
                throw std::runtime_error("Invalid item type at spawnpoint");
        }

        i++;
    }
}


void Match::load_spawn_points() {
    auto yaml_maps = *resource_pool->get_yaml(MAPS_FILE);
    auto yaml_path = yaml_maps["maps"][map]["yaml"].as<std::string>();
    auto yaml = *resource_pool->get_yaml(yaml_path);

    if (yaml.IsNull()) {
        std::cerr << "Error loading yaml file" << std::endl;
        exit(1);
    }
    std::transform(yaml["player_spawnpoints"].begin(), yaml["player_spawnpoints"].end(),
                   std::back_inserter(player_spawn_points), [](const YAML::Node& sp) {
                       return engine::Vector2D(sp["x"].as<int>(), sp["y"].as<int>());
                   });

    std::transform(yaml["enemy_spawnpoints"].begin(), yaml["enemy_spawnpoints"].end(),
                   std::back_inserter(enemy_spawn_points), [](const YAML::Node& sp) {
                       return engine::Vector2D(sp["x"].as<int>(), sp["y"].as<int>());
                   });

    std::transform(yaml["item_spawnpoints"].begin(), yaml["item_spawnpoints"].end(),
                   std::back_inserter(item_spawn_points), [](const YAML::Node& sp) {
                       return engine::Vector2D(sp["x"].as<int>(), sp["y"].as<int>());
                   });
}


void Match::initiate_enemies(std::vector<character_t> enemy_types) {

    // create a hashmap that stores vector of size 4
    std::map<character_t, std::vector<int>> get_wh;

    std::transform(enemy_types.begin(), enemy_types.end(), std::inserter(get_wh, get_wh.end()),
                   [&](const character_t& enemy_type) -> std::pair<character_t, std::vector<int>> {
                       auto enemy_resources_ptr =
                               resource_pool->get_yaml(map_character_enum_to_string.at(enemy_type));
                       if (!enemy_resources_ptr || enemy_resources_ptr->IsNull()) {
                           std::cerr << "Error loading yaml file" << std::endl;
                           exit(1);
                       }
                       const auto& enemy_resources = *enemy_resources_ptr;
                       return {enemy_type,
                               {enemy_resources["body_width"].as<int>(),
                                enemy_resources["body_height"].as<int>()}};
                   });

    // this is to avoid having the same id as a player, i doubt we will have 100 players, in the
    // future we can change this to a more robust solution
    int i = 1;
    if (enemy_spawn_points.empty()) {
        throw std::runtime_error("No enemy spawn points found in map.");
    }

    for (auto& spawn_point: enemy_spawn_points) {

        character_t current_enemy_type = enemy_types[i % enemy_types.size()];


        if (current_enemy_type == LIZARD_GOON) {
            auto lizard_goon = std::make_shared<LizardGoon>(
                    i, spawn_point.x, spawn_point.y, get_wh[LIZARD_GOON][0], get_wh[LIZARD_GOON][1],
                    resource_pool->get_config());
            collision_manager->track_dynamic_body(lizard_goon);
            enemies.emplace_back(lizard_goon);
        } else if (current_enemy_type == MAD_HATTER) {
            auto mad_hatter = std::make_shared<MadHatter>(
                    i, spawn_point.x, spawn_point.y, get_wh[MAD_HATTER][0], get_wh[MAD_HATTER][1],
                    resource_pool->get_config());
            collision_manager->track_dynamic_body(mad_hatter);
            enemies.emplace_back(mad_hatter);

        } else {
            throw std::runtime_error("Invalid enemy type");
        }
        i++;
    }
}

void Match::delete_disconnected_player(id_client_t id_client) {
    std::unique_lock<std::mutex> lock(match_mutex);
    for (auto player = players.begin(); player != players.end(); ++player) {
        if (id_client == (*player).second->get_id()) {
            //            collision_manager->remove_object(
            //                    reinterpret_cast<const
            //                    std::shared_ptr<engine::CollisionObject>&>(*player));
            players.erase(player);
#ifdef LOG_VERBOSE
            std::cout << "Player " << id_client << " disconnected from match " << std::endl;
#endif
            break;
        }
    }
}

//-------------------- Getter Methods -----------------

Queue<std::shared_ptr<Message>>& Match::get_match_queue() { return match_queue; }

size_t Match::get_num_players() const { return players.size(); }

uint16_t Match::get_map() const { return map; }

size_t Match::get_max_players() const { return max_players; }

std::shared_ptr<Player> Match::get_player(size_t id) {

    auto player = players.find(id);
    if (player != players.end()) {
        return player->second;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

std::vector<size_t> Match::get_clients_ids() {
    std::vector<size_t> ids;
    std::transform(players.begin(), players.end(), std::back_inserter(ids),
                   [](const auto& pair) { return static_cast<size_t>(pair.first); });
    return ids;
}
