#include "./recv_create_game.h"

//#include "../../../../server/game_logic/matches_manager.h"

RecvCreateGameMessage::RecvCreateGameMessage(uint16_t client_id, const std::string& match_name) {
    this->id_client = client_id;
    this->match_name = match_name;
}

void RecvCreateGameMessage::run(/*MatchesManager& matches_manager*/) {
    //    matches_manager.create_new_match(id_client, match_name, 2, "map 1");
}

void RecvCreateGameMessage::send_message(CommonProtocol& protocol) {
    //   protocol.send_cheat_command();
}

RecvCreateGameMessage::~RecvCreateGameMessage() {}
