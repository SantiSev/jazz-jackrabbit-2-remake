#ifndef TP_FINAL_MATCH_H
#define TP_FINAL_MATCH_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../../server/game_logic/characters/enemy.h"
#include "../../server/game_logic/characters/player.h"
#include "../protocol/match_message_handler.h"
#include "../protocol/server_thread_manager.h"
#include "./client_monitor.h"


class Match: public Thread {
private:
    bool online;
    bool match_has_ended = false;
    int match_time = STARTING_MATCH_TIME;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> event_queue;  // shared with the receiver
    std::list<ServerThreadManager*> clients;
    MatchMessageHandler message_handler;
    std::vector<Player> players;
    std::vector<Enemy> enemies;
    std::vector<std::string> items;
    size_t players_connected = 0;
    size_t required_players;
    size_t minutes = STARTING_MATCH_TIME / 60;
    size_t seconds = STARTING_MATCH_TIME % 60;
    ClientMonitor client_monitor;
    uint8_t map;

public:
    // Constructor
    explicit Match(const uint8_t& map, size_t required_players);
    void run() override;
    // Kill the thread
    void stop() override;
    // Destroyer
    ~Match() = default;

    Player& get_player(size_t id);

    void add_player_to_game(const std::string& player_name, const uint8_t& character);

    GameStateDTO create_actual_snapshot();

    bool has_match_ended() const;

    std::string get_match_name() const;

    size_t get_num_players();

    size_t get_max_players() const;

    int get_minutes();

    int get_seconds();

    void countdown_match(std::chrono::time_point<std::chrono::system_clock>& runTime,
                         const std::chrono::time_point<std::chrono::system_clock>& endTime);

    void send_end_message_to_players();

    void add_client_to_match(ServerThreadManager* client, const std::string& player_name,
                             const uint8_t& character);

    std::vector<size_t> get_clients_ids();

    uint8_t get_map() const;

    void run_command(const CommandDTO& dto);

    bool is_command_valid(command_t command);

    void update_players();

    void update_enemies();

    void initiate_enemies();
};

#endif
