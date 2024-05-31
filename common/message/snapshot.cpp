#include "snapshot.h"

Snapshot::Snapshot(std::vector<Player>& players, std::vector<Enemies>& enemies):
        players(players), enemies(enemies) {}

const std::vector<Player>& Snapshot::get_players() const { return players; }

const std::vector<Enemies>& Snapshot::get_enemies() const { return enemies; }

void Snapshot::set_players(const std::vector<Player>& new_players) { players = new_players; }

void Snapshot::set_enemies(const std::vector<Enemies>& new_enemies) { enemies = new_enemies; }

int Snapshot::get_minutes() const { return minutes; }

int Snapshot::get_seconds() const { return seconds; }

void Snapshot::set_minutes(const int& new_minutes) { minutes = new_minutes; }

void Snapshot::set_seconds(const int& new_seconds) { seconds = new_seconds; }

SnapshotDTO Snapshot::to_dto() const {
    SnapshotDTO dto;
    dto.players = players;
    dto.enemies = enemies;
    dto.minutes = minutes;
    dto.seconds = seconds;
    return dto;
}
