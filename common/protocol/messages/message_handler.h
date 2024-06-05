#ifndef TP_FINAL_MESSAGE_HANDLER_H
#define TP_FINAL_MESSAGE_HANDLER_H

#include "../common_dto.h"

class MessageHandler {

public:
    // matches_manager
    virtual void handle_recv_create_game(const CreateGameDTO& dto) {}
    virtual void handle_recv_join_match(const JoinMatchDTO& dto) {}
    virtual void handle_request_active_games(const RequestActiveGamesDTO& dto) {}

    // client
    virtual void handle_acpt_connection(const id_client_t& i) {}
    virtual void handle_recv_close_connection() {}
    virtual void handle_joined_match(const ClientJoinedMatchDTO& dto) {}
    virtual void handle_game_created(const GameCreatedDTO& dto) {}
    virtual void handle_recv_active_games(const MatchInfoDTO& dto) {}
    virtual void handle_recv_command(const CommandDTO& command) {}
};

#endif