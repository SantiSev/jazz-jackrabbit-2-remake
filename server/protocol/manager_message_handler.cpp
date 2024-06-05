#include "manager_message_handler.h"

#include "../game_logic/matches_manager.h"

void MatchesManagerMessageHandler::handle_recv_create_game(const CreateGameDTO& dto) {
    matches_manager.create_new_match(dto);
}

void MatchesManagerMessageHandler::handle_recv_join_match(const JoinMatchDTO& dto) {
    matches_manager.join_match(dto);
}

void MatchesManagerMessageHandler::handle_request_active_games(const RequestActiveGamesDTO& dto) {
    matches_manager.send_match_lists(dto);
}
