#include "match_message_handler.h"

#include "../game_logic/match.h"


void MatchMessageHandler::handle_recv_command(const CommandDTO& command) {
    match.run_command(command);
}

void MatchMessageHandler::handle_recv_cheat_command(const CheatCommandDTO& cheat_command) {
    //    match.run_cheat_command(cheat_command);
}

void MatchMessageHandler::handle_recv_close_connection(const CloseConnectionDTO& dto) {
    match.delete_disconnected_player(dto.id_client);
}
