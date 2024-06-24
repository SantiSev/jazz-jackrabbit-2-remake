#ifndef TP_FINAL_CONFIGURATION_H
#define TP_FINAL_CONFIGURATION_H

#include <memory>

#include <yaml-cpp/yaml.h>

class Configuration {
public:
    Configuration();

    // Match config
    int match_max_players;
    int match_max_matches;
    int match_points_enemy;
    int match_points_player;
    int match_points_coin;
    int match_duration;

    // Map editor config
    int map_ed_max_height;
    int map_ed_max_width;

    // Enemy match config
    int enemy_health;
    int enemy_damage;
    int enemy_respawn_cool_down;
    int enemy_speed;
    int enemy_falling_speed;
    int enemy_move_rng;

    // Player match config
    int player_health;
    int player_speed_x;
    int player_sprint_spd;
    int player_jump_f;
    int player_falling_speed;
    int player_respawn_cool_down;
    int player_invincivility_cool_down;
    int player_intoxication_cool_down;
    int player_can_sprint;

    // Bullet match config
    int bullet_base_dmg;
    int bullet_base_speed;
    int bullet_base_ammo;
    int bullet_base_max_ammo;
    int bullet_base_shoot_rate;

    void load_yaml_info(const std::shared_ptr<YAML::Node>& config);
    //    void load_yaml_info(const YAML::Node& config);

    ~Configuration();
};

#endif
