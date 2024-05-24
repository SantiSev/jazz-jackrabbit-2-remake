#ifndef TP_FINAL_SERVER_GAMELOOP_H
#define TP_FINAL_SERVER_GAMELOOP_H

#include <string>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "server_enemies.h"
#include "server_player.h"

class Server_Gameloop: public Thread {
private:
    bool online;
    Queue<std::string>& event_queue;
    std::vector<Player> players;
    std::vector<Enemies> enemies;

public:
    // Constructor
    explicit Server_Gameloop(Queue<std::string>& event_queue);
    void run() override;
    // Kill the thread
    void stop() override;
    // Destroyer
    ~Server_Gameloop() override = default;

    Player& get_player(size_t id);
};


#endif
