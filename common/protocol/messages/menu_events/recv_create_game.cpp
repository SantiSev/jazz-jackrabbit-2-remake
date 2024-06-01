#include "./recv_create_game.h"

#include "../../../../server/game_logic/matches_manager.h"

RecvCreateGameMessage::RecvCreateGameMessage(uint16_t client_id, const std::string& match_name,
                                             const uint8_t& character_selected) {
    this->id_client = client_id;
    this->match_name = match_name;
    this->character = character_selected;
}

void RecvCreateGameMessage::run(MatchesManager& matches_manager) {
    matches_manager.create_new_match(id_client, match_name, REQUIRED_PLAYERS_TO_START, "map 1",
                                     character);
}

void RecvCreateGameMessage::run() {}

void RecvCreateGameMessage::send_message(CommonProtocol& protocol) {
    //   protocol.send_cheat_command();
}

RecvCreateGameMessage::~RecvCreateGameMessage() {}
