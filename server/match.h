#ifndef TP_FINAL_MATCH_H
#define TP_FINAL_MATCH_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../common/common_constants.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/message/message.h"
#include "../common/message/snapshot.h"
#include "game_logic/characters/enemies.h"
#include "game_logic/characters/player.h"
#include "game_logic/client_monitor.h"

#include "test_client_server.h"


class Match: public Thread {
private:
    bool online;
    bool match_has_ended = false;
    std::string match_name;
    int match_time = STARTING_MATCH_TIME;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> event_queue;  // shared with the receiver
    std::list<TestClientServer*> clients;
    std::vector<Player> players;
    std::vector<Enemies> enemies;
    std::vector<std::string> items;
    size_t players_connected = 0;
    size_t required_players;
    ClientMonitor client_monitor;
    std::string& map;
    Snapshot snapshot;

public:
    // Constructor
    explicit Match(const std::string& map, std::string match_name, size_t required_players);
    void run() override;
    // Kill the thread
    void stop() override;
    // Destroyer
    ~Match() = default;

    Player& get_player(size_t id);

    void add_player_to_game(Player& player);

    void create_actual_snapshot(int const seconds, int const minutes);

    bool has_match_ended() const;

    std::string get_match_name() const;

    size_t get_num_players();

    size_t get_max_players() const;

    int get_minutes();

    int get_seconds();

    void countdown_match(std::chrono::time_point<std::chrono::system_clock>& runTime,
                         const std::chrono::time_point<std::chrono::system_clock>& endTime,
                         int& minutes, int& seconds);

    void send_end_message_to_players();

    void add_client_to_match(TestClientServer* client);
};

#endif
