#include "snapshot.h"

Snapshot::Snapshot(std::vector<Player>& players, std::vector<Enemies>& enemies):
        players(players), enemies(enemies) {}

const std::vector<Player>& Snapshot::get_players() const { return players; }

const std::vector<Enemies>& Snapshot::get_enemies() const { return enemies; }

void Snapshot::set_players(const std::vector<Player>& new_players) { players = new_players; }

void Snapshot::set_enemies(const std::vector<Enemies>& new_enemies) { enemies = new_enemies; }
