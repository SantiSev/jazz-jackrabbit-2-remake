#include "./recv_create_game.h"

RecvCreateGameMessage::RecvCreateGameMessage(uint16_t id_player, const std::string& match_name) {
    this->id_player = id_player;
    this->match_name = match_name;
}

void RecvCreateGameMessage::run() {}

RecvCreateGameMessage::~RecvCreateGameMessage() {}