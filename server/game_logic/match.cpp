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
    initiate_enemies();
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
        while (online) {
            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> delta = endTime - startTime;
            startTime = endTime;

            auto frameStart = std::chrono::system_clock::now();
            std::shared_ptr<Message> message;

            size_t events = 0;
            while (match_queue.try_pop(message) && events < MAX_EVENTS_PER_LOOP) {

                events++;
                if (message) {
#ifdef LOG_VERBOSE
                    std::cout << "message received about to being runned" << std::endl;
#endif
                    message->run(message_handler);
                }
            }

            collision_manager->update();
            collision_manager->remove_inactive_bodies();

            respawn_enemies();
            respawn_players();
            respawn_items();

            countdown_match(runTime, endTime);

            auto snapshot = create_actual_snapshot();
            auto snapshot_message = std::make_shared<SendGameStateMessage>(snapshot);
            client_monitor.broadcastClients(snapshot_message);

            auto frameEnd = std::chrono::system_clock::now();
            delta = frameEnd - frameStart;

            if (match_has_ended) {
                online = false;
            }

            if (delta.count() < FPSMAX) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(static_cast<int>(FPSMAX - delta.count())));
            }
        }
        stop();
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
    if (match_time != 0 && !match_has_ended) {
        if (std::chrono::duration_cast<std::chrono::seconds>(endTime - runTime).count() >= 1) {
            match_time--;
            runTime = endTime;
            size_t minutes = match_time / 60;
            size_t seconds = match_time % 60;
            std::cout << "Time Remaining: " << std::setw(2) << std::setfill('0') << minutes << ":"
                      << std::setw(2) << std::setfill('0') << seconds << std::endl;
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
#ifdef LOG_VERBOSE
    std::cout << "Running command with id " << dto.id_player << "" << std::endl;
#endif
    std::shared_ptr<Player> player = get_player(dto.id_player);
    if (player) {
#ifdef LOG_VERBOSE
        std::cout << dto.id_player << "says: " << command_to_string.at(dto.command) << std::endl;
#endif
        player->execute_command(dto.command);
    }
}

void Match::respawn_players() {
    for (auto& pair: players) {
        auto& player = pair.second;
        if (player->try_revive()) {
            player->revive(player->position);
        }
    }
}
void Match::respawn_enemies() {
    for (auto& enemy: enemies) {
        if (enemy->try_revive()) {
            enemy->revive(enemy->spawn_position);
        }
    }
}

void Match::respawn_items() {
    for (auto& item: items) {
        if (item->try_respawn()) {
            item->respawn(item->position);
        }
    }
}

Vector2D Match::select_player_spawn_point() {
    int i = rand() % player_spawn_points.size();
    return player_spawn_points[i];
}


//-------------------- Conection Methods -----------------

void Match::add_player_to_game(const AddPlayerDTO& dto) {
    players_connected++;

    Vector2D pos = select_player_spawn_point();
    auto new_player = std::make_shared<Player>(dto.id_client, dto.name, dto.player_character, pos.x,
                                               pos.y, *collision_manager);
    collision_manager->track_dynamic_body(new_player);

#ifdef LOG_VERBOSE
    std::cout << "Player connected: " << dto.id_client << "is playing as "
              << map_character_enum_to_string.at(dto.player_character) << std::endl;
#endif

    players.insert({dto.id_client, std::move(new_player)});
    //    players[dto.id_client] = new_player;
}

void Match::send_end_message_to_players() {
    //    auto game_ended_message = std::make_shared<SendFinishMatchMessage>();
    //    client_monitor.broadcastClients(game_ended_message);

    auto close_connection_message = std::make_shared<CloseConnectionMessage>(CloseConnectionDTO());
    client_monitor.broadcastClients(close_connection_message);
}

bool Match::has_match_ended() const { return match_has_ended; }

void Match::stop() {
    online = false;
#ifdef LOG_VERBOSE
    std::cout << "stopping match " << std::endl;
#endif
    //    event_queue->close();
    send_end_message_to_players();
    client_monitor.remove_all_queues();
    players.clear();
#ifdef LOG_VERBOSE
    std::cout << "clients cleared in match" << std::endl;
#endif
}

GameStateDTO Match::create_actual_snapshot() {
    GameStateDTO game_state{};
    game_state.seconds = (uint16_t)match_time % 60;
    game_state.num_players = players.size();
    game_state.num_enemies = enemies.size();
    game_state.num_bullets = bullets.size();

    size_t i = 0;
    for (auto& player_pair: players) {
        game_state.players[i].id = player_pair.first;
        snprintf(game_state.players[i].name, sizeof(game_state.players[i].name), "%s",
                 player_pair.second->get_name().c_str());
        game_state.players[i].health = player_pair.second->get_health();
        game_state.players[i].points = player_pair.second->get_points();
        game_state.players[i].character = player_pair.second->get_character();
        game_state.players[i].state = player_pair.second->get_state();
        game_state.players[i].x_pos = player_pair.second->position.x;
        game_state.players[i].y_pos = player_pair.second->position.y;
        for (size_t j = 0; j < NUM_OF_WEAPONS; ++j) {
            game_state.players[i].weapons[j].ammo = player_pair.second->get_weapon(j)->get_ammo();
            game_state.players[i].weapons[j].is_empty =
                    player_pair.second->get_weapon(j)->get_ammo() == 0 ? (uint8_t)1 : (uint8_t)0;
            game_state.players[i].weapons[j].weapon_name =
                    (uint8_t)player_pair.second->get_weapon(j)->get_weapon_id();
        }
        ++i;
    }
    for (size_t j = 0; j < enemies.size(); ++j) {
        game_state.enemies[j].id = enemies[j]->get_id();
        game_state.enemies[j].state = enemies[j]->get_state();
        game_state.enemies[j].character = enemies[j]->get_character();
        game_state.enemies[j].x_pos = enemies[j]->position.x;
        game_state.enemies[j].y_pos = enemies[j]->position.y;
    }
    for (size_t k = 0; k < bullets.size(); ++k) {
        game_state.bullets[k].id = bullets[k]->get_id();
        game_state.bullets[k].direction = bullets[k]->get_direction();
        game_state.bullets[k].bullet_type = bullets[k]->get_type();
        game_state.bullets[k].x_pos = bullets[k]->position.x;
        game_state.bullets[k].y_pos = bullets[k]->position.y;
    }

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

    for (auto obj: yaml["player_spawnpoints"]) {
        auto x = obj["x"].as<int>();
        auto y = obj["y"].as<int>();
        player_spawn_points.emplace_back(x, y);
    }

    for (auto obj: yaml["enemy_spawnpoints"]) {
        auto x = obj["x"].as<int>();
        auto y = obj["y"].as<int>();
        enemy_spawn_points.emplace_back(x, y);
    }
}


void Match::initiate_enemies() {
    int i = 1;
    if (enemy_spawn_points.empty()) {
        throw std::runtime_error("No enemy spawn points found in map.");
    }
    for (auto& spawn_point: enemy_spawn_points) {
        if (i % 2 == 0) {
            auto lizard_goon = std::make_shared<LizardGoon>(i, spawn_point.x, spawn_point.y);
            collision_manager->track_dynamic_body(lizard_goon);
            enemies.emplace_back(lizard_goon);
        } else {
            auto mad_hatter = std::make_shared<MadHatter>(i, spawn_point.x, spawn_point.y);
            collision_manager->track_dynamic_body(mad_hatter);
            enemies.emplace_back(mad_hatter);
        }
        i++;
    }
}

void Match::delete_disconnected_player(id_client_t id_client) {
    std::unique_lock<std::mutex> lock(match_mutex);
    for (auto player = players.begin(); player != players.end(); ++player) {
        if (id_client == (*player).second->get_id()) {
            collision_manager->remove_object(
                    reinterpret_cast<const std::shared_ptr<CollisionObject>&>(*player));
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
