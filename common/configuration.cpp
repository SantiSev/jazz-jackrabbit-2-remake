#include "configuration.h"

Configuration::Configuration(const std::shared_ptr<YAML::Node>& config) {
    auto c = *config;

    auto match = c["match"];
    match_max_players = match["max_players"].as<int>();
    match_max_matches = match["max_matches_to_create"].as<int>();
    match_points_enemy = match["kill_points_enemy"].as<int>();
    match_points_player = match["kill_points_player"].as<int>();
    match_points_coin = match["coin_points"].as<int>();
    match_duration = match["match_duration"].as<int>();

    auto map_ed = c["map_editor"];
    map_ed_max_height = map_ed["map_height"].as<int>();
    map_ed_max_width = map_ed["map_width"].as<int>();

    auto enemy = c["enemy"];
    enemy_health = enemy["health"].as<int>();
    enemy_damage = enemy["damage"].as<int>();
    enemy_respawn_cool_down = enemy["respawn_time"].as<int>();
    enemy_speed = enemy["speed"].as<int>();
    enemy_falling_speed = enemy["falling_speed"].as<int>();
    enemy_move_rng = enemy["movement_range"].as<int>();

    auto player = c["player"];
    player_health = player["health"].as<int>();
    player_speed_x = player["speed_x"].as<int>();
    player_sprint_spd = player["sprint_speed"].as<int>();
    player_jump_f = player["jump_force"].as<int>();
    player_falling_speed = player["falling_speed"].as<int>();
    player_respawn_cool_down = player["respawn_time"].as<int>();
    player_invincivility_cool_down = player["invulnerability_time"].as<int>();
    player_intoxication_cool_down = player["intoxication_time"].as<int>();
    player_can_sprint = player["is_sprint_allowed"].as<int>();

    auto bullet = c["bullet"];
    bullet_base_dmg = bullet["base_damage"].as<int>();
    bullet_base_speed = bullet["base_speed"].as<int>();
    bullet_base_ammo = bullet["base_ammo"].as<int>();
    bullet_base_max_ammo = bullet["base_max_ammo"].as<int>();
    bullet_base_shoot_rate = bullet["base_shoot_rate"].as<int>();
}

Configuration::~Configuration() = default;
