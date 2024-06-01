#include "match.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>

#include "../common/protocol/messages/in_game_events/send_game_state.h"

Match::Match(const std::string& map, std::string match_name, size_t required_players_setting):
        online(true),
        match_name(std::move(match_name)),
        event_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()),
        players(),
        enemies(),
        required_players(required_players_setting),
        map(const_cast<std::string&>(map)),
        snapshot(players, enemies) {}

void Match::run() {
    try {
        while (online && players.size() != required_players) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Match: " << match_name
                      << " Waiting for all players to connect to start..." << std::endl;
        }
        auto startTime = std::chrono::system_clock::now();
        auto runTime = startTime;

        const double FPSMAX = 1000.0 / 60.0;
        std::shared_ptr<Message> next_message;
        int minutes;
        int seconds;

        while (online) {
            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> delta = endTime - startTime;
            startTime = endTime;

            auto frameStart = std::chrono::system_clock::now();

            size_t events = 0;
            while (event_queue->try_pop(next_message) && events < MAX_EVENTS_PER_LOOP) {
                events++;
                next_message->run();
            }

            //            if (get_player(1).get_health() != 0) {
            //                get_player(1).decrease_health(10);
            //                std::cout << get_player(1).get_health() << std::endl;
            //                std::cout << get_player(1).get_name() << std::endl;
            //            }

            countdown_match(runTime, endTime, minutes, seconds);

            create_actual_snapshot(seconds, minutes);

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
                            const std::chrono::time_point<std::chrono::system_clock>& endTime,
                            int& minutes, int& seconds) {
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

void Match::create_actual_snapshot(int const& seconds, int const& minutes) {
    snapshot.set_enemies(enemies);
    snapshot.set_players(players);
    snapshot.set_seconds(seconds);
    snapshot.set_minutes(minutes);
}

bool Match::has_match_ended() const { return match_has_ended; }

std::string Match::get_match_name() const { return match_name; }

void Match::add_player_to_game(const std::string& player_name, std::string character) {
    players_connected++;
    Player new_player(players_connected, player_name, std::move(character));
    new_player.set_id(players_connected);
    players.push_back(new_player);
}

void Match::add_client_to_match(ServerThreadManager* client, const std::string& player_name,
                                std::string character) {
    client_monitor.addClient(client->get_sender_queue());
    client->set_receiver_queue(event_queue);
    clients.push_back(client);
    add_player_to_game(player_name, std::move(character));
}

size_t Match::get_num_players() { return players.size(); }

size_t Match::get_max_players() const { return required_players; }

int Match::get_minutes() { return snapshot.get_minutes(); }

int Match::get_seconds() { return snapshot.get_seconds(); }

void Match::send_end_message_to_players() {
    //        client_monitor.broadcastClients(game_ended_message);
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
