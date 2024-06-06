#include "GamePlayer.h"

#include <utility>

GamePlayer::GamePlayer(const uint16_t& id, const uint8_t& character, const uint8_t& state,
                       std::string name):
        id(id), name(std::move(name)), character(character), state(state) {}

uint8_t GamePlayer::get_id() const { return id; }

void GamePlayer::set_health(uint16_t health_updated) { health = health_updated; }

void GamePlayer::set_points(uint16_t points_updated) { points = points_updated; }

void GamePlayer::set_state(uint8_t state_updated) { state = state_updated; }