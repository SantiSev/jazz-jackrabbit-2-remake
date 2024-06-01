#include "./recv_join_match.h"

#include "../../../../server/game_logic/matches_manager.h"

RecvJoinMatchMessage::RecvJoinMatchMessage(uint16_t client_id, uint16_t id_match,
                                           uint8_t player_character) {
    this->id_client = client_id;
    this->id_match = id_match;
    this->player_character = player_character;
}

void RecvJoinMatchMessage::send_message(CommonProtocol& protocol) {
    //   protocol.send_cheat_command();
}

void RecvJoinMatchMessage::run() {}

RecvJoinMatchMessage::~RecvJoinMatchMessage() {}

void RecvJoinMatchMessage::run(MatchesManager& matches_manager) {
    matches_manager.join_match(id_client, id_match, player_character);
}
