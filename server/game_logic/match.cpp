#include "match.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>

Match::Match(const uint8_t& map_selected, size_t required_players_setting):
        online(true),
        event_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()),
        message_handler(*this),
        players({}),
        enemies({}),
        items(0),
        required_players(required_players_setting),
        client_monitor(),
        map(map_selected) {
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
            minutes = match_time / 60;
            seconds = match_time % 60;
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

Player& Match::get_player(size_t id) {
    auto it = std::find_if(players.begin(), players.end(),
                           [id](const Player& player) { return player.get_id() == id; });
    if (it != players.end()) {
        return *it;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

GameStateDTO Match::create_actual_snapshot() {
    GameStateDTO game_state{};

    game_state.num_players = players.size();
    for (size_t i = 0; i < players.size(); ++i) {
        game_state.players[i].id = players[i].get_id();
        snprintf(game_state.players[i].name, sizeof(game_state.players[i].name), "%s",
                 players[i].get_name().c_str());
        game_state.players[i].health = players[i].get_health();
        game_state.players[i].character = players[i].get_character();
        game_state.players[i].points = players[i].get_points();
        game_state.players[i].state = players[i].get_state();
        for (size_t j = 0; j < NUM_OF_WEAPONS; ++j) {
            game_state.players[i].weapons[j].ammo = players[i].get_weapon(j).get_ammo();
            game_state.players[i].weapons[j].is_empty =
                    players[i].get_weapon(j).is_weapon_empty() ? (uint8_t)1 : (uint8_t)0;
            game_state.players[i].weapons[j].weapon_name =
                    (uint8_t)players[i].get_weapon(j).get_weapon_name();
        }
    }
    game_state.seconds = (uint16_t)seconds;

    return game_state;
}

bool Match::has_match_ended() const { return match_has_ended; }

uint8_t Match::get_map() const { return map; }

void Match::add_player_to_game(const std::string& player_name, const uint8_t& character) {
    players_connected++;
    Player new_player(players_connected, player_name, character);
    new_player.set_id(players_connected);
    players.push_back(new_player);
}

void Match::add_client_to_match(ServerThreadManager* client, const std::string& player_name,
                                const uint8_t& character) {
    client_monitor.addClient(client->get_sender_queue());
    client->set_receiver_queue(event_queue);
    clients.push_back(client);
    add_player_to_game(player_name, character);
}

size_t Match::get_num_players() { return players.size(); }

size_t Match::get_max_players() const { return required_players; }

void Match::send_end_message_to_players() {
    auto game_ended_message = std::make_shared<CloseConnectionMessage>();
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
    //    event_queue->close();
    send_end_message_to_players();
    //    for (auto& client: clients) {
    //        client->get_sender_queue()->close();
    //    }
    client_monitor.remove_all_queues();
}

void Match::run_command(const CommandDTO& dto) {
    Player& player = get_player(dto.id_player);
    if (!player.is_player_alive()) {
        return;
    }
    if (!is_command_valid(dto.command)) {
        return;
    }
    switch (dto.command) {
        case MOVE_LEFT:
            //            player.move_left();
            player.set_state(STATE_MOVING_LEFT);
            break;
        case MOVE_RIGHT:
            //            player.move_right();
            player.set_state(STATE_MOVING_RIGHT);
            break;
        case MOVE_LEFT_FAST:
            //            player.move_left_fast();
            player.set_state(STATE_SPRINTING_LEFT);
            break;
        case MOVE_RIGHT_FAST:
            //            player.move_right_fast();
            player.set_state(STATE_SPRINTING_RIGHT);
            break;
        case JUMP:
            if (!player.is_player_jumping()) {
                //                player.jump();
            }
            player.set_state(STATE_JUMPING);
            break;
        case ESPECIAL_ATTACK:
            if (player.is_player_intoxicated() || !player.is_special_available()) {
                break;
            }
            //            player.especial_attack();
            player.set_state(STATE_ESPECIAL_ATTACKING);  // ver si importa el is_facing_to_the_right
            player.reset_special_attack();
            break;
        case LOOK_UP:
            //            player.look_up();
            player.set_state(STATE_AIMING_UP);
            break;
        case DUCK_DOWN:
            //            player.duck_down();
            player.set_state(STATE_CROUNCHING);
            break;
        case SHOOT:
            if (!player.is_player_intoxicated()) {
                //                player.shoot();
                if (player.is_facing_to_the_right()) {
                    player.set_state(STATE_SHOOTING_RIGHT);
                } else {
                    player.set_state(STATE_SHOOTING_LEFT);
                }
            }
            break;
        case TAUNT:
            player.set_state(STATE_TAUNTING);
            break;
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
        if (!player.is_player_alive()) {
            if (player.can_revive()) {
                player.revive();
                player.set_state(STATE_IDLE_RIGHT);
                // reset_player_pos_to_spawn_point(player);
            } else {
                player.decrease_revive_cooldown();
            }
        }
        if (player.is_player_intoxicated()) {
            player.decrease_intoxication_cooldown();
            if (player.get_intoxication_cooldown() == 0) {
                if (player.is_facing_to_the_right()) {
                    player.set_state(STATE_IDLE_RIGHT);
                } else {
                    player.set_state(STATE_IDLE_LEFT);
                }
                player.reset_intoxication();
            }
        }
        if (!player.is_special_available()) {
            player.decrease_special_attack_cooldown();
        }
        if (player.is_player_alive() && player.get_health() == MIN_HEALTH) {
            player.kill_player();
            player.set_state(STATE_DEAD);
            // player.set_velocity_to_zero();
            player.reset_revive_cooldown();
        }
    }
}

void Match::update_enemies() {
    for (auto& enemy: enemies) {
        if (!enemy.is_enemy_alive()) {
            if (enemy.can_revive()) {
                enemy.revive();
                enemy.set_state(STATE_IDLE_RIGHT);
                // reset_player_pos_to_spawn_point(player);
            } else {
                enemy.decrease_revive_cooldown();
            }
        }
        if (enemy.is_enemy_alive() && enemy.get_health() == MIN_HEALTH) {
            enemy.kill();
            enemy.set_state(STATE_DEAD);
            // enemy.set_velocity_to_zero();
            enemy.reset_revive_cooldown();
        }
    }
}

void Match::initiate_enemies() {
    for (size_t i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy(20, 20, i % 3, i);
        // set_spawn_point_to_enemy(enemy);
        enemies.emplace_back(enemy);
    }
}
