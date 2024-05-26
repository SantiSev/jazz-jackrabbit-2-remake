#ifndef TP_FINAL_SERVER_GAMELOOP_H
#define TP_FINAL_SERVER_GAMELOOP_H

#include <memory>
#include <string>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/message/message.h"
#include "game_logic/snapshot.h"

#include "server_enemies.h"
#include "server_player.h"

class ServerGameloop: public Thread {
private:
    bool online;
    bool match_has_ended = false;
    std::string match_name;
    int match_time = STARTING_MATCH_TIME;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> event_queue;  // shared with the receiver
    std::shared_ptr<Queue<Snapshot>> snapshot_queue;               // shared with the sender
    std::vector<Player> players;
    std::vector<Enemies> enemies;
    std::vector<std::string> items;
    size_t players_connected = 0;
    size_t required_players;
    std::string map;
    Snapshot snapshot;

public:
    // Constructor
    explicit ServerGameloop(std::shared_ptr<Queue<std::shared_ptr<Message>>> event_queue,
                            std::shared_ptr<Queue<Snapshot>> snapshot_queue, std::string match_name,
                            size_t required_players);
    void run() override;
    // Kill the thread
    void stop() override;
    // Destroyer
    ~ServerGameloop() = default;

    Player& get_player(size_t id);

    void add_player_to_game(Player& player);

    void create_actual_snapshot(int const seconds, int const minutes);

    bool has_match_ended() const;

    std::string get_match_name() const;

    size_t get_num_players();

    size_t get_max_players() const;

    int get_minutes();

    int get_seconds();
};

#endif
