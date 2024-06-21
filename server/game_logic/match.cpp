#include "match.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>

#include "../../common/assets.h"

Match::Match(const map_list_t& map_selected, size_t required_players_setting,
             Queue<std::shared_ptr<Message>>& lobby_queue, ClientMonitor& monitor,
             const std::shared_ptr<engine::ResourcePool>& resource_pool):
        online(true),
        lobby_queue(lobby_queue),
        message_handler(*this),
        players({}),
        enemies({}),
        bullets({}),
        items({}),
        required_players(required_players_setting),
        client_monitor(monitor),
        map(map_selected),
        collision_manager(nullptr),
        resource_pool(resource_pool),
        match_queue(Queue<std::shared_ptr<Message>>()) {
    load_enviorment(map_selected);
    load_spawn_points();
    initiate_enemies({character_t::MAD_HATTER, character_t::LIZARD_GOON});
}

void Match::run() {
    try {

        /* while (online && players.size() != required_players) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Match map: " << map << " Waiting for all players to connect to
        start..."
        << std::endl;
        } */

        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        auto startTime = std::chrono::system_clock::now();
        auto runTime = startTime;

        const double FPSMAX = 1000.0 / 60.0;
#ifdef LOG_VERBOSE
        std::cout << "Match map: " << map_list_to_string.at(map) << " Starting..." << std::endl;
#endif
        while (!match_has_ended && online) {
            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> delta = endTime - startTime;
            startTime = endTime;

            auto frameStart = std::chrono::system_clock::now();
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

            countdown_match(runTime, endTime);

            auto snapshot = create_actual_snapshot();
            auto snapshot_message = std::make_shared<SendGameStateMessage>(snapshot);
            client_monitor.broadcastClients(snapshot_message);

            auto frameEnd = std::chrono::system_clock::now();
            delta = frameEnd - frameStart;

            if (delta.count() < FPSMAX) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(static_cast<int>(FPSMAX - delta.count())));
            }
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


void Match::countdown_match(std::chrono::time_point<std::chrono::system_clock>& runTime,
                            const std::chrono::time_point<std::chrono::system_clock>& endTime) {
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
            std::cout << "Game Over" << std::endl;
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
        if (player->try_revive() || cheat_revive_enabled) {

            bool can_be_placed = false;
            Vector2D new_position = get_random_spawn_point(player_spawn_points);
            while (!can_be_placed) {
                can_be_placed = collision_manager->can_be_placed(
                        player, new_position);  // chequeo si la posicion es valida
                if (!can_be_placed) {
                    new_position = get_random_spawn_point(player_spawn_points);
                }
            }

            player->revive(get_random_spawn_point(player_spawn_points));
            collision_manager->track_dynamic_body(player);
        }
    }
}
void Match::respawn_enemies() {
    for (auto& enemy: enemies) {
        if (enemy->try_revive() || cheat_revive_enabled) {
            std::cout << "| ENEMY respawned with ID:" << enemy->get_id() << " |" << std::endl;
            enemy->revive(enemy.get()->spawn_position);  // TODO set to random spawn position
            collision_manager->track_dynamic_body(enemy);
        }
    }
}

void Match::respawn_items() {
    for (auto& item: items) {
        if (item->try_respawn()) {
            std::cout << "Item respawned" << std::endl;
            item->respawn(item.get()->position);
            collision_manager->track_dynamic_body(item);
        }
    }
}

Vector2D Match::get_random_spawn_point(std::vector<Vector2D> const& spawnpoints) {
    if (spawnpoints.empty()) {
        throw std::runtime_error("No spawn points found in map.");
    }
    int i = rand() % player_spawn_points.size();
    return player_spawn_points[i];
}

void Match::run_cheat_command(const CheatCommandDTO& dto) {
    if (dto.command == CHEAT_KILL_ALL) {
        kill_all_cheat();
    } else if (dto.command == CHEAT_REVIVE_ALL) {
        revive_all_cheat();
    } else if (dto.command == CHEAT_REVIVE) {
        std::shared_ptr<Player> player = get_player(dto.id_player);
        if (player) {
            player->revive(get_random_spawn_point(player_spawn_points));
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

void Match::revive_all_cheat() {
    cheat_revive_enabled = true;
    respawn_enemies();
    respawn_players();
    cheat_revive_enabled = false;
}

//-------------------- Conection Methods -----------------

void Match::add_player_to_game(const AddPlayerDTO& dto) {
    Vector2D pos = get_random_spawn_point(player_spawn_points);

    auto player_resources_ptr =
            resource_pool->get_yaml(map_character_enum_to_string.at(dto.player_character));

    if (!player_resources_ptr || player_resources_ptr->IsNull()) {
        std::cerr << "Error loading yaml file" << std::endl;
        exit(1);
    }

    int player_width = (*player_resources_ptr)["body_width"].as<int>();
    int player_height = (*player_resources_ptr)["body_height"].as<int>();

    switch (dto.player_character) {
        case JAZZ_CHARACTER: {

            auto jazz_player =
                    std::make_shared<Jazz>(dto.id_client, dto.name, pos.x, pos.y, player_width,
                                           player_height, *collision_manager);
            collision_manager->track_dynamic_body(jazz_player);
            players[dto.id_client] = jazz_player;
            break;
        }
        case SPAZ_CHARACTER: {

            auto spaz_player =
                    std::make_shared<Spaz>(dto.id_client, dto.name, pos.x, pos.y, player_width,
                                           player_height, *collision_manager);
            collision_manager->track_dynamic_body(spaz_player);
            players[dto.id_client] = spaz_player;
            break;
        }
        case LORI_CHARACTER: {

            auto lori_player =
                    std::make_shared<Lori>(dto.id_client, dto.name, pos.x, pos.y, player_width,
                                           player_height, *collision_manager);
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
    GameStateDTO game_state{};  // TODO memset
    game_state.seconds = (uint16_t)match_time % 60;

    game_state.num_players = players.size();
    size_t i = 0;
    for (auto player = players.begin(); player != players.end(); ++player) {
        game_state.players[i].id = player->second->get_id();
        snprintf(game_state.players[i].name, sizeof(game_state.players[i].name), "%s",
                 player->second->get_name().c_str());
        game_state.players[i].health = player->second->get_health();
        game_state.players[i].points = player->second->get_points();
        game_state.players[i].character = player->second->get_character();
        game_state.players[i].state = player->second->get_state();
        game_state.players[i].x_pos = player->second->position.x;
        game_state.players[i].y_pos = player->second->position.y;
        for (size_t j = 0; j < NUM_OF_WEAPONS; ++j) {
            game_state.players[i].weapons[j].ammo = player->second->get_weapon(j)->get_ammo();
            game_state.players[i].weapons[j].is_empty =
                    player->second->get_weapon(j)->get_ammo() == 0 ? (uint8_t)1 : (uint8_t)0;
            game_state.players[i].weapons[j].weapon_name =
                    (uint8_t)player->second->get_weapon(j)->get_weapon_id();
        }
        ++i;
    }

    game_state.num_enemies = 0;
    for (const auto& enemy: enemies) {
        if (!enemy->is_dead()) {
            auto& enemy_state = game_state.enemies[game_state.num_enemies];
            enemy_state.id = enemy->get_id();
            enemy_state.state = enemy->get_state();
            enemy_state.character = enemy->get_character();
            enemy_state.x_pos = enemy->position.x;
            enemy_state.y_pos = enemy->position.y;
            game_state.num_enemies++;
        }
    }

    game_state.num_bullets = 0;
    collision_manager->iterateDynamicBodies(
            [&game_state](const std::shared_ptr<DynamicBody>& body) {
                auto bullet = std::dynamic_pointer_cast<Bullet>(body);

                if (bullet) {

                    game_state.bullets[game_state.num_bullets].id = bullet->get_id();
                    game_state.bullets[game_state.num_bullets].direction = bullet->get_direction();
                    game_state.bullets[game_state.num_bullets].bullet_type = bullet->get_type();
                    game_state.bullets[game_state.num_bullets].x_pos = bullet->position.x;
                    game_state.bullets[game_state.num_bullets].y_pos = bullet->position.y;
                    game_state.num_bullets++;
                }
            });
    return game_state;
}

//-------------------- Initialization Methods -----------------


void Match::load_enviorment(map_list_t selected_map) {
    auto yaml = *resource_pool->get_yaml(map_list_to_string.at(selected_map));

    if (yaml.IsNull()) {
        throw std::runtime_error("Error loading yaml file");
    }
    int grid_width = yaml["map_width"].as<int>();
    int grid_height = yaml["map_height"].as<int>();

    if (grid_width <= 0 || grid_height <= 0) {
        throw std::runtime_error("Invalid map size");
    }

    collision_manager = std::make_unique<CollisionManager>(grid_width, grid_height);

    std::cout << "Loading map..." << std::endl;

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

#ifdef LOG
    std::cout << "Map loaded!" << std::endl;
#endif
}


void Match::load_spawn_points() {
    auto yaml = *resource_pool->get_yaml(map_list_to_string.at(map));

    if (yaml.IsNull()) {
        std::cerr << "Error loading yaml file" << std::endl;
        exit(1);
    }

    std::transform(yaml["player_spawnpoints"].begin(), yaml["player_spawnpoints"].end(),
                   std::back_inserter(player_spawn_points), [](const YAML::Node& sp) {
                       return Vector2D(sp["x"].as<int>(), sp["y"].as<int>());
                   });

    std::transform(yaml["enemy_spawnpoints"].begin(), yaml["enemy_spawnpoints"].end(),
                   std::back_inserter(enemy_spawn_points), [](const YAML::Node& sp) {
                       return Vector2D(sp["x"].as<int>(), sp["y"].as<int>());
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
    int i = 0;
    if (enemy_spawn_points.empty()) {
        throw std::runtime_error("No enemy spawn points found in map.");
    }

    for (auto& spawn_point: enemy_spawn_points) {

        character_t current_enemy_type = enemy_types[i % enemy_types.size()];


        if (current_enemy_type == LIZARD_GOON) {
            auto lizard_goon =
                    std::make_shared<LizardGoon>(i, spawn_point.x, spawn_point.y,
                                                 get_wh[LIZARD_GOON][0], get_wh[LIZARD_GOON][1]);
            collision_manager->track_dynamic_body(lizard_goon);
            enemies.emplace_back(lizard_goon);
        } else if (current_enemy_type == MAD_HATTER) {
            auto mad_hatter = std::make_shared<MadHatter>(
                    i, spawn_point.x, spawn_point.y, get_wh[MAD_HATTER][0], get_wh[MAD_HATTER][1]);
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
            //                    std::shared_ptr<CollisionObject>&>(*player));
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

size_t Match::get_num_players() { return players.size(); }

map_list_t Match::get_map() const { return map; }

size_t Match::get_max_players() const { return required_players; }

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
