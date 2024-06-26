#ifndef TP_FINAL_MATCH_H
#define TP_FINAL_MATCH_H

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../../common/assets.h"
#include "../../common/item_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/physics_engine/collision_manager.h"
#include "../../server/game_logic/weapons/bullet.h"
#include "../protocol/match_message_handler.h"
#include "../protocol/server_thread_manager.h"
#include "./client_monitor.h"
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
    int match_time = 300;
    Queue<std::shared_ptr<Message>>& lobby_queue;
    MatchMessageHandler message_handler;

    std::unordered_map<uint16_t, std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<Collectable>> items;

    size_t players_connected = 0;
    size_t max_players;
    ClientMonitor& client_monitor;
    uint16_t map;
    std::unique_ptr<engine::CollisionManager> collision_manager;
    std::vector<Vector2D> player_spawn_points;
    std::vector<Vector2D> enemy_spawn_points;
    std::vector<Vector2D> item_spawn_points;
    std::mutex match_mutex;

    const std::shared_ptr<engine::ResourcePool>& resource_pool;

    //-------------------- Gameloop Methods ----------------------

    void countdown_match(std::chrono::time_point<std::chrono::steady_clock>& runTime,
                         const std::chrono::time_point<std::chrono::steady_clock>& endTime);

    void respawn_players();

    void respawn_enemies();

    void respawn_items();

    Collectable create_random_item(Vector2D position);

    Vector2D get_random_spawn_point(std::vector<Vector2D> const& spawnpoints);

    //-------------------- Initialization Methods -----------------

    void load_environment();

    void initiate_enemies(std::vector<character_t> enemy_types);

    void load_spawn_points();

    void load_items();

public:
    Queue<std::shared_ptr<Message>> match_queue;
    // Constructor
    explicit Match(const uint16_t& map_selected, size_t required_players_setting,
                   Queue<std::shared_ptr<Message>>& lobby_queue, ClientMonitor& monitor,
                   const std::shared_ptr<engine::ResourcePool>& resource_pool);
    void run() override;
    void stop() override;
    ~Match() override = default;

    void run_command(const CommandDTO& dto);

    //-------------------- Conection Methods ----------------------

    void add_player_to_game(const AddPlayerDTO& dto);

    void send_end_message_to_players();

    void delete_disconnected_player(id_client_t id_client);

    GameStateDTO create_actual_snapshot();

    void run_cheat_command(const CheatCommandDTO& dto);

    void kill_all_cheat();

    //-------------------- Getter Methods -----------------

    std::shared_ptr<Player> get_player(size_t id);

    bool has_match_ended() const;

    size_t get_num_players() const;

    size_t get_max_players() const;

    std::vector<size_t> get_clients_ids();

    uint16_t get_map() const;

    Queue<std::shared_ptr<Message>>& get_match_queue();
};

#endif
