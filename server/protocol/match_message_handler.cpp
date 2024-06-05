#include "match_message_handler.h"

#include "../game_logic/match.h"


void MatchMessageHandler::handle_recv_command(const CommandDTO& command) {
    match.run_command(command);
}
