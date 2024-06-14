#ifndef TP_FINAL_MESSAGE_HANDLER_H
#define TP_FINAL_MESSAGE_HANDLER_H

#include "../common_dto.h"

class MessageHandler {

public:
    // All
    virtual void handle_recv_close_connection(const CloseConnectionDTO& dto) {}

    // Matches manager
    virtual void handle_recv_create_game(const CreateGameDTO& dto) {}
    virtual void handle_recv_join_match(const JoinMatchDTO& dto) {}
    virtual void handle_request_active_games(const RequestActiveGamesDTO& dto) {}

    // Match
    virtual void handle_add_player(const AddPlayerDTO& dto) {}
    virtual void handle_recv_cheat_command(const CheatCommandDTO& cheat_command) {}

    // Client
    virtual void handle_acpt_connection(const id_client_t& i) {}

    virtual void handle_connected_to_match(const ClientHasConnectedToMatchDTO& dto) {}
    virtual void handle_recv_active_games(const MatchInfoDTO& dto) {}
    virtual void handle_recv_command(const CommandDTO& command) {}
    virtual void handle_recv_game_state(const GameStateDTO& dto) {}
    virtual void handle_recv_finish_match() {}
};

#endif
