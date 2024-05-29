#include "./recv_create_game.h"

#include <iostream>

RecvCreateGameMessage::RecvCreateGameMessage(uint16_t id_player, const std::string& match_name) {
    this->match_name = match_name;
    this->id_player = id_player;
}

void RecvCreateGameMessage::run() {}

RecvCreateGameMessage::~RecvCreateGameMessage() {}
