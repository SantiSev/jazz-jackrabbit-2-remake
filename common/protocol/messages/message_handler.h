#ifndef TP_FINAL_MESSAGE_HANDLER_H
#define TP_FINAL_MESSAGE_HANDLER_H

#include "../common_dto.h"

class MessageHandler {

public:
    // matches_manager
    virtual void handle_recv_create_game(const CreateGameDTO& dto) {}
    virtual void handle_recv_join_match(JoinMatchDTO dto) {}

    // client
    virtual void handle_acpt_connection(const id_client_t& i) {}
    virtual void handle_recv_close_connection() {}
    virtual void handle_joined_match(ClientJoinedMatchDTO dto) {}
    virtual void handle_game_created(GameCreatedDTO dto) {}
};


#endif
