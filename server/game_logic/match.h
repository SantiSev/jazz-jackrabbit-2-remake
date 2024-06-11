

#ifndef TP_FINAL_MATCH_H
#define TP_FINAL_MATCH_H

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../../common/assets.h"
#include "../../game_engine/physics_engine/collision_manager.h"
#include "../../server/game_logic/weapons/bullet.h"
#include "../protocol/match_message_handler.h"
#include "../protocol/server_thread_manager.h"
#include "characters/enemies.h"
#include "characters/players.h"
#include "collectables/collectable_items.h"
#include "platforms/box_platform.h"
#include "weapons/guns.h"

#include "client_monitor.h"

class Player;
class Enemy;
class Bullet;
class Collectable;

class Match: public Thread {
private:
    bool online;
    bool match_has_ended = false;
    int match_time = MATCH_DURATION;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> event_queue;  // shared with the receiver
    std::shared_ptr<Queue<std::shared_ptr<Message>>>& lobby_queue;
    std::list<ServerThreadManager*> clients;
    MatchMessageHandler message_handler;

    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<Collectable>> items;

    size_t players_connected = 0;
    size_t required_players;
    ClientMonitor client_monitor;
    map_list_t map;
    std::unique_ptr<CollisionManager> collision_manager;
    std::vector<Vector2D> player_spawn_points;
    std::vector<Vector2D> enemy_spawn_points;

public:
    // Constructor
    explicit Match(const map_list_t& map_selected, size_t required_players_setting,
                   std::shared_ptr<Queue<std::shared_ptr<Message>>>& lobby_queue);

    void run() override;
    void stop() override;
    ~Match() override = default;

    //-------------------- Gameloop Methods ----------------------

    void countdown_match(std::chrono::time_point<std::chrono::system_clock>& runTime,
                         const std::chrono::time_point<std::chrono::system_clock>& endTime);

    void respawn_players();

    void respawn_enemies();

    void respawn_items();

    void run_command(const CommandDTO& dto);

    Vector2D select_player_spawn_point();

    //-------------------- Conection Methods ----------------------

    // un add playuer to match

    void add_player_to_game(const std::string& player_name, const character_t& character,
                            uint16_t client_id);

    void add_client_to_match(ServerThreadManager* client, const std::string& player_name,
                             const character_t& character);

    void send_end_message_to_players();

    void delete_disconnected_player(id_client_t id_client);

    GameStateDTO create_actual_snapshot();

    //-------------------- Initialization Methods -----------------

    void load_enviorment(map_list_t map);

    void initiate_enemies();

    void load_spawn_points();

    void load_map(const map_list_t& map_selected);

    //-------------------- Getter Methods -----------------

    std::shared_ptr<Player> get_player(size_t id);

    bool has_match_ended() const;

    std::string get_match_name() const;

    size_t get_num_players();

    size_t get_max_players() const;

    std::vector<size_t> get_clients_ids();

    map_list_t get_map() const;

    ServerThreadManager& get_client_by_id(id_client_t id_client);

    void erase_client_from_list(id_client_t id_client);
};

#endif
