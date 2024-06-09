#include "match.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>

#include "../../common/assets.h"

Match::Match(const map_list_t& map_selected, size_t required_players_setting):
        online(true),
        event_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()),
        message_handler(*this),
        players({}),
        enemies({}),
        items(0),
        required_players(required_players_setting),
        client_monitor(),
        map(map_selected),
        collision_manager(800, 600) {
    load_spawn_points();
    initiate_enemies();
}

void Match::run() {
    try {
        //        while (online && players.size() != required_players) {
        //            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //            std::cout << "Match map: " << map << " Waiting for all players to connect to
        //            start..."
        //                      << std::endl;
        //        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        auto startTime = std::chrono::system_clock::now();
        auto runTime = startTime;

        const double FPSMAX = 1000.0 / 60.0;
        std::shared_ptr<Message> next_message;
        std::cout << "Match map: " << map_list_to_string.at(map) << " Starting..." << std::endl;
        while (online) {
            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> delta = endTime - startTime;
            startTime = endTime;

            auto frameStart = std::chrono::system_clock::now();

            size_t events = 0;
            while (event_queue->try_pop(next_message) && events < MAX_EVENTS_PER_LOOP) {
                events++;
                next_message->run(message_handler);
            }

            patrol_move_enemies();
            collision_manager.update();
            update_enemies();
            update_players();

            countdown_match(runTime, endTime);

            auto snapshot = create_actual_snapshot();
            auto snapshot_message = std::make_shared<SendGameStateMessage>(snapshot);
            client_monitor.broadcastClients(snapshot_message);

            auto frameEnd = std::chrono::system_clock::now();
            delta = frameEnd - frameStart;

            if (match_has_ended) {
                break;
            }

            if (delta.count() < FPSMAX) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(static_cast<int>(FPSMAX - delta.count())));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

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
        }
    }
}

std::shared_ptr<Player> Match::get_player(size_t id) {
    auto it = std::find_if(
            players.begin(), players.end(),
            [id](const std::shared_ptr<Player>& player) { return player->get_id() == id; });
    if (it != players.end()) {
        return *it;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

GameStateDTO Match::create_actual_snapshot() {
    GameStateDTO game_state{};
    game_state.seconds = (uint16_t)match_time % 60;
    game_state.num_players = players.size();
    game_state.num_enemies = enemies.size();
    game_state.num_bullets = bullets.size();

    for (size_t i = 0; i < players.size(); ++i) {
        game_state.players[i].id = players[i]->get_id();
        snprintf(game_state.players[i].name, sizeof(game_state.players[i].name), "%s",
                 players[i]->get_name().c_str());
        game_state.players[i].health = players[i]->get_health();
        game_state.players[i].points = players[i]->get_points();
        game_state.players[i].character = players[i]->get_character();
        game_state.players[i].state = players[i]->get_state();
        game_state.players[i].x_pos = players[i].get()->position.x;
        game_state.players[i].y_pos = players[i].get()->position.y;
        for (size_t j = 0; j < NUM_OF_WEAPONS; ++j) {
            game_state.players[i].weapons[j].ammo = players[i]->get_weapon(j).get_ammo();
            game_state.players[i].weapons[j].is_empty =
                    players[i]->get_weapon(j).is_weapon_empty() ? (uint8_t)1 : (uint8_t)0;
            game_state.players[i].weapons[j].weapon_name =
                    (uint8_t)players[i]->get_weapon(j).get_weapon_id();
        }
    }
    for (size_t i = 0; i < players.size(); ++i) {
        game_state.players[i].state = enemies[i]->get_state();
        game_state.enemies[i].x_pos = enemies[i]->position.x;
        game_state.enemies[i].y_pos = enemies[i]->position.y;
        game_state.enemies[i].state = enemies[i]->get_state();
    }
    for (size_t i = 0; i < bullets.size(); ++i) {
        game_state.bullets[i].x_pos = bullets[i]->position.x;
        game_state.bullets[i].y_pos = bullets[i]->position.y;
        game_state.bullets[i].bullet_type = (uint8_t)bullets[i]->get_bullet_type();
    }


    return game_state;
}

bool Match::has_match_ended() const { return match_has_ended; }

map_list_t Match::get_map() const { return map; }

void Match::add_player_to_game(const std::string& player_name, const character_t& character,
                               uint16_t client_id) {
    players_connected++;
    Vector2D pos = select_player_spawn_point();
    auto new_player = std::make_shared<Player>(client_id, player_name, character, pos.x, pos.y,
                                               collision_manager);
    new_player->set_id(players_connected);  // todo integrar a player
    collision_manager.track_dynamic_body(new_player);
    players.push_back(new_player);
}

void Match::add_client_to_match(ServerThreadManager* client, const std::string& player_name,
                                const character_t& character) {
    client_monitor.addClient(client->get_sender_queue());
    client->set_receiver_queue(event_queue);
    clients.push_back(client);
    add_player_to_game(player_name, character, client->get_client_id());
    std::cout << "Player connected: " << player_name << "is playing as "
              << character_to_string(character) << std::endl;
}

size_t Match::get_num_players() { return players.size(); }

size_t Match::get_max_players() const { return required_players; }

void Match::send_end_message_to_players() {
    auto game_ended_message = std::make_shared<SendFinishMatchMessage>();
    client_monitor.broadcastClients(game_ended_message);
}

std::vector<size_t> Match::get_clients_ids() {
    std::vector<size_t> ids;
    std::transform(clients.begin(), clients.end(), std::back_inserter(ids),
                   [](auto& client) { return client->get_client_id(); });
    return ids;
}

void Match::stop() {
    online = false;
    collision_manager.clear();
    //    event_queue->close();
    send_end_message_to_players();
    //    for (auto& client: clients) {
    //        client->get_sender_queue()->close();
    //    }
    client_monitor.remove_all_queues();
}

void Match::run_command(const CommandDTO& dto) {
    std::shared_ptr<Player> player = get_player(dto.id_player);
    if (!player->is_player_alive()) {
        return;
    }
    if (!is_command_valid(dto.command)) {
        return;
    }
    switch (dto.command) {
        case MOVE_LEFT:
            player->move_left();
            if (player->is_on_floor()) {
                if (player->is_player_intoxicated()) {
                    player->set_state(STATE_INTOXICATED_MOV_LEFT);
                } else {
                    player->set_state(STATE_MOVING_LEFT);
                }
            }
            break;
        case MOVE_RIGHT:
            player->move_right();
            if (player->is_on_floor()) {
                if (player->is_player_intoxicated()) {
                    player->set_state(STATE_INTOXICATED_MOV_RIGHT);
                } else {
                    player->set_state(STATE_MOVING_RIGHT);
                }
            }
            break;
        case MOVE_LEFT_FAST:
            if (player->is_on_floor()) {
                // player.move_left_fast();
                player->set_state(STATE_SPRINTING_LEFT);
            }
            break;
        case MOVE_RIGHT_FAST:
            if (player->is_on_floor()) {
                // player.move_right_fast();
                player->set_state(STATE_SPRINTING_RIGHT);
            }
            break;
        case JUMP:
            if (!player->is_on_floor()) {
                break;
            }

            player->jump();
            if (player->is_facing_right()) {
                player->set_state(STATE_JUMPING_RIGHT);
            } else {
                player->set_state(STATE_JUMPING_LEFT);
            }
            break;
        case SPECIAL_ATTACK:
            if (player->is_player_intoxicated() || !player->is_special_available()) {
                break;
            }
            //            player.especial_attack();
            if (player->is_facing_right()) {
                player->set_state(STATE_ESPECIAL_RIGHT);
            } else {
                player->set_state(STATE_ESPECIAL_LEFT);
            }
            player->reset_special_attack();
            break;
        // case SHOOT:
        //     if (!player->is_player_intoxicated()) {
        //         player->shoot();

        //         Bullet bullet = player->shoot();
        //         collision_manager.add_dynamic_body(bullet);
        //         bullets.emplace_back(bullet);

        //         if (player->is_facing_right()) {
        //             player->set_state(STATE_SHOOTING_RIGHT);
        //         } else {
        //             player->set_state(STATE_SHOOTING_LEFT);
        //         }
        //     }
        //     break;
        default:
            break;
    }
}

bool Match::is_command_valid(command_t command) {
    if (command <= 0x00 || command > 0x12) {
        return false;
    }
    return true;
}

void Match::update_players() {
    for (auto& player: players) {
        if (!player->is_player_alive()) {
            if (player->can_revive()) {
                player->revive(select_player_spawn_point());
            } else {
                player->decrease_revive_cooldown();
            }
        }
        if (player->is_player_intoxicated()) {
            player->decrease_intoxication_cooldown();
            if (player->get_intoxication_cooldown() == 0) {
                player->reset_intoxication();
            }
        }
        if (!player->is_special_available()) {
            player->decrease_special_attack_cooldown();
        }
        if (player->is_player_alive() && player->get_health() == MIN_HEALTH) {
            player->kill_player();
            player->set_state(STATE_DEAD);
            player->reset_revive_cooldown();
        }
        if (player->is_on_floor() && (player->get_state() == STATE_FALLING)) {
            if (player->is_facing_right()) {
                player->set_state(STATE_IDLE_RIGHT);
            } else {
                player->set_state(STATE_IDLE_LEFT);
            }
        }
        if (!player->is_on_floor() && (player->velocity.y > 0) && player->is_doing_action_state()) {
            player->set_state(STATE_FALLING);
        }
    }
}

void Match::update_enemies() {
    for (auto& enemy: enemies) {
        if (!enemy->is_enemy_alive()) {
            if (enemy->can_revive()) {
                enemy->revive();

                // reset_player_pos_to_spawn_point(player);
            } else {
                enemy->decrease_revive_cooldown();
            }
        }
        if (enemy->is_enemy_alive() && enemy->get_health() == MIN_HEALTH) {
            enemy->kill();
            enemy->set_state(STATE_DEAD);
            enemy->reset_revive_cooldown();
        }
    }
}

void Match::initiate_enemies() {
    int i = 1;
    for (auto& spawn_point: enemy_spawn_points) {
        auto new_enemy = std::make_shared<Enemy>(i % 3, i, spawn_point.x, spawn_point.y);
        new_enemy->set_spawn_point(spawn_point);
        collision_manager.track_dynamic_body(new_enemy);
        enemies.emplace_back(new_enemy);
        i++;
    }
}

Vector2D Match::select_player_spawn_point() {
    int i = rand() % player_spawn_points.size();
    return player_spawn_points[i];
}

void Match::patrol_move_enemies() {
    for (auto& enemy: enemies) {
        if (enemy->is_enemy_alive()) {
            if (abs(match_time % 2) == 0) {
                if (enemy->is_facing_right()) {
                    enemy->move_left();
                    enemy->set_state(STATE_MOVING_LEFT);
                } else {
                    enemy->move_right();
                    enemy->set_state(STATE_MOVING_RIGHT);
                }
            }
        }
    }
}


void Match::load_spawn_points() {
    std::string file_path = map_list_to_string.at(map) + YAML_EXTENSION;

    YAML::Node yaml = YAML::LoadFile(file_path);
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

void Match::delete_disconnected_player(id_client_t id_client) {
    for (auto player = players.begin(); player != players.end(); ++player) {
        if (id_client == (*player)->get_id()) {
            players.erase(player);
            break;
        }
    }
}
