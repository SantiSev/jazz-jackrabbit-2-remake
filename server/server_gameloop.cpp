#include "server_gameloop.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>

#include "../common/common_constants.h"

ServerGameloop::ServerGameloop(std::shared_ptr<Queue<std::shared_ptr<Message>>> event_queue,
                               std::shared_ptr<Queue<Snapshot>> snapshot_queue,
                               std::string match_name, size_t required_players_setting):
        online(true),
        match_name(std::move(match_name)),
        event_queue(std::move(event_queue)),
        snapshot_queue(std::move(snapshot_queue)),
        players(),
        enemies(),
        required_players(required_players_setting),
        snapshot(players, enemies) {}

void ServerGameloop::run() {
    try {
        Player player(0, "pepe", "mago");
        add_player_to_game(player);
        while (online && players.size() != required_players) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Waiting for all players to connect to start..." << std::endl;
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
            while (event_queue->try_pop(next_message) && events < MAX_EVENTS_PER_LOOP && online) {
                events++;
                next_message->run(reinterpret_cast<ServerEventloop*>(this));
            }
            if (get_player(1).get_health() != 0) {
                get_player(1).decrease_health(10);
                std::cout << get_player(1).get_health() << std::endl;
                std::cout << get_player(1).get_name() << std::endl;
            }

            if (match_time != 0 && !match_has_ended) {
                if (std::chrono::duration_cast<std::chrono::seconds>(endTime - runTime).count() >=
                    1) {
                    match_time--;
                    runTime = endTime;
                    minutes = match_time / 60;
                    seconds = match_time % 60;
                    std::cout << "Time Remaining: " << std::setw(2) << std::setfill('0') << minutes
                              << ":" << std::setw(2) << std::setfill('0') << seconds << std::endl;
                }
            } else {
                if (!match_has_ended) {
                    std::cout << "Game Over" << std::endl;
                    match_time = true;
                }
            }

            create_actual_snapshot(seconds, minutes);
            snapshot_queue->push(snapshot);

            auto frameEnd = std::chrono::system_clock::now();
            delta = frameEnd - frameStart;

            if (delta.count() < FPSMAX) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(static_cast<int>(FPSMAX - delta.count())));
            }
        }
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

void ServerGameloop::add_player_to_game(Player& player) {
    players_connected++;
    player.set_id(players_connected);
    players.push_back(player);
}

Player& ServerGameloop::get_player(size_t id) {
    auto it = std::find_if(players.begin(), players.end(),
                           [id](const Player& player) { return player.get_id() == id; });
    if (it != players.end()) {
        return *it;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

void ServerGameloop::create_actual_snapshot(int const seconds, int const minutes) {
    snapshot.set_enemies(enemies);
    snapshot.set_players(players);
    snapshot.set_seconds(seconds);
    snapshot.set_minutes(minutes);
}

bool ServerGameloop::has_match_ended() const { return match_has_ended; }

std::string ServerGameloop::get_match_name() const { return match_name; }

void ServerGameloop::stop() {
    online = false;
    event_queue->close();
    snapshot_queue->close();
}

size_t ServerGameloop::get_num_players() { return players.size(); }

size_t ServerGameloop::get_max_players() const { return required_players; }

int ServerGameloop::get_minutes() { return snapshot.get_minutes(); }

int ServerGameloop::get_seconds() { return snapshot.get_seconds(); }
