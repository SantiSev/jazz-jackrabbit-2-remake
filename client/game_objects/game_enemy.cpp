#include "game_enemy.h"


GameEnemy::GameEnemy(const uint8_t& enemy_type, const uint8_t& state):
        state(state), enemy_type(enemy_type) {}

void GameEnemy::set_health(uint16_t updated_health) { health = updated_health; }

void GameEnemy::set_state(uint8_t updated_state) { state = updated_state; }

void GameEnemy::set_position(int x, int y) {
    position_x = x;
    position_y = y;
}
