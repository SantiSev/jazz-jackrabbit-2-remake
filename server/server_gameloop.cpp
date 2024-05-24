#include "server_gameloop.h"

#include <algorithm>
#include <string>


Server_Gameloop::Server_Gameloop(Queue<std::string>& event_queue):
        online(true), event_queue(event_queue) {}

void Server_Gameloop::run() {
    try {
        Player player(0, "pepe", "mago");
        players.push_back(player);
        while (online) {

            std::string next_event;
            while (event_queue.try_pop(next_event)) {}

            get_player(0).decrease_health(10);
            std::cout << get_player(0).get_health() << std::endl;
            std::cout << get_player(0).get_name() << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}


Player& Server_Gameloop::get_player(size_t id) {
    auto it = std::find_if(players.begin(), players.end(),
                           [id](const Player& player) { return player.get_id() == id; });
    if (it != players.end()) {
        return *it;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

void Server_Gameloop::stop() { online = false; }
