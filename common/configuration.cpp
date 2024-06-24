#include "configuration.h"

Configuration::Configuration():
        match_max_players(0),
        match_max_matches(0),
        match_points_enemy(0),
        match_points_player(0),
        match_points_coin(0),
        match_duration(0),
        map_ed_max_height(0),
        map_ed_max_width(0),
        enemy_health(0),
        enemy_damage(0),
        enemy_spawn_cd(0),
        enemy_speed(0),
        enemy_jump_f(0),
        enemy_gravity(0),
        enemy_move_rng(0),
        player_health(0),
        player_speed_x(0),
        player_sprint_spd(0),
        player_jump_f(0),
        player_gravity(0),
        player_spawn_cd(0),
        player_invincivility_cd(0),
        player_intoxication_cd(0),
        player_can_sprint(1),
        bullet_base_dmg(0),
        bullet_base_speed(0),
        bullet_base_ammo(0),
        bullet_base_max_ammo(0),
        bullet_base_shoot_rate(0) {}

Configuration::~Configuration() = default;

// void Configuration::load_yaml_info(const YAML::Node& config){
void Configuration::load_yaml_info(const std::shared_ptr<YAML::Node>& config) {
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
    enemy_spawn_cd = enemy["respawn_time"].as<int>();
    enemy_speed = enemy["speed"].as<int>();
    enemy_jump_f = enemy["jump_force"].as<int>();
    enemy_gravity = enemy["gravity"].as<int>();
    enemy_move_rng = enemy["movement_range"].as<int>();
    auto player = c["player"];
    player_health = player["health"].as<int>();
    player_speed_x = player["speed_x"].as<int>();
    player_sprint_spd = player["sprint_speed"].as<int>();
    player_jump_f = player["jump_speed"].as<int>();
    player_gravity = player["gravity"].as<int>();
    player_spawn_cd = player["respawn_time"].as<int>();
    player_invincivility_cd = player["invulnerability_time"].as<int>();
    player_intoxication_cd = player["intoxication_time"].as<int>();
    player_can_sprint = player["is_sprint_allowed"].as<int>();
    auto bullet = c["bullet"];
    bullet_base_dmg = bullet["base_damage"].as<int>();
    bullet_base_speed = bullet["base_speed"].as<int>();
    bullet_base_ammo = bullet["base_ammo"].as<int>();
    bullet_base_max_ammo = bullet["base_max_ammo"].as<int>();
    bullet_base_shoot_rate = bullet["base_shoot_rate"].as<int>();
}
