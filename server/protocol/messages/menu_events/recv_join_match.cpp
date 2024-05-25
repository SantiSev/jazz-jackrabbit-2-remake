#include "./recv_join_match.h"

RecvJoinMatchMessage::RecvJoinMatchMessage(uint16_t id_player, uint16_t id_match,
                                           uint8_t player_character) {
    this->id_player = id_player;
    this->id_match = id_match;
    this->player_character = player_character;
}

void RecvJoinMatchMessage::run() {}

RecvJoinMatchMessage::~RecvJoinMatchMessage() {}
