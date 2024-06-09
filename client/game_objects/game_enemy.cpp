#include "game_enemy.h"


GameEnemy::GameEnemy(const uint8_t& enemy_type, const uint8_t& state):
        state(state), enemy_type(enemy_type) {}

void GameEnemy::set_state(uint8_t updated_state) { state = updated_state; }

uint8_t GameEnemy::get_state() const { return state; }

void GameEnemy::set_position(int x, int y) {
    position_x = x;
    position_y = y;
}
