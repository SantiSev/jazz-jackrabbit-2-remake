#include "server_gameloop.h"

#include <algorithm>
#include <chrono>
#include <memory>
#include <string>

#include "../common/common_constants.h"

Server_Gameloop::Server_Gameloop(Queue<Message>& event_queue, Queue<Snapshot>& snapshot_queue):
        online(true),
        event_queue(event_queue),
        snapshot_queue(snapshot_queue),
        players(),
        enemies(),
        snapshot(players, enemies) {}

void Server_Gameloop::run() {
    try {
        auto startTime = std::chrono::system_clock::now();
        const double FPSMAX = 1000.0 / 60.0;
        Player player(0, "pepe", "mago");
        add_player_to_game(player);
        Message next_message(0);

        while (online) {
            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> delta = endTime - startTime;
            startTime = endTime;

            auto frameStart = std::chrono::system_clock::now();

            size_t events = 0;
            while (event_queue.try_pop(next_message) && events < MAX_EVENTS_PER_LOOP) {
                events++;
                next_message.run(reinterpret_cast<ServerEventloop*>(this));
            }

            get_player(0).decrease_health(10);
            std::cout << get_player(0).get_health() << std::endl;
            std::cout << get_player(0).get_name() << std::endl;
            create_actual_snapshot();
            snapshot_queue.push(snapshot);

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

void Server_Gameloop::add_player_to_game(Player& player) { players.push_back(player); }

Player& Server_Gameloop::get_player(size_t id) {
    auto it = std::find_if(players.begin(), players.end(),
                           [id](const Player& player) { return player.get_id() == id; });
    if (it != players.end()) {
        return *it;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

void Server_Gameloop::create_actual_snapshot() {
    snapshot.set_enemies(enemies);
    snapshot.set_players(players);
}

void Server_Gameloop::stop() { online = false; }
