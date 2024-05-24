#ifndef TP_FINAL_SERVER_GAMELOOP_H
#define TP_FINAL_SERVER_GAMELOOP_H

#include <string>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/message/message.h"
#include "game_logic/snapshot.h"

#include "server_enemies.h"
#include "server_player.h"

class Server_Gameloop: public Thread {
private:
    bool online;
    Queue<Message>& event_queue;      // shared with the receiver
    Queue<Snapshot>& snapshot_queue;  // shared with the sender
    std::vector<Player> players;
    std::vector<Enemies> enemies;
    Snapshot snapshot;

public:
    // Constructor
    explicit Server_Gameloop(Queue<Message>& event_queue, Queue<Snapshot>& snapshot_queue);
    void run() override;
    // Kill the thread
    void stop() override;
    // Destroyer
    ~Server_Gameloop() override = default;

    Player& get_player(size_t id);

    void add_player_to_game(Player& player);

    void create_actual_snapshot();
};


#endif
