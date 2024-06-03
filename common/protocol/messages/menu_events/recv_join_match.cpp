#include "./recv_join_match.h"

#include "../../../../server/game_logic/matches_manager.h"

RecvJoinMatchMessage::RecvJoinMatchMessage(JoinMatchDTO& join_match):
        Message(RECV_JOIN_MATCH), join_match(join_match) {}

void RecvJoinMatchMessage::run() {}

void RecvJoinMatchMessage::run(MatchesManager& matches_manager) {
    matches_manager.join_match(join_match.id_player, join_match.id_match,
                               join_match.player_character);
}

void RecvJoinMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_join_match(header, join_match);
}

RecvJoinMatchMessage::~RecvJoinMatchMessage() {}
