#ifndef TP_FINAL_CLIENT_MESSAGE_HANDLER_H
#define TP_FINAL_CLIENT_MESSAGE_HANDLER_H

#include "../../common/protocol/messages/common_message.h"
#include "../../common/protocol/messages/message_handler.h"

class ClientThreadManager;

class ClientMessageHandler: public MessageHandler {
private:
    ClientThreadManager& client;
    //    Queue<std::shared_ptr<Message>>& queue;

public:
    explicit ClientMessageHandler(ClientThreadManager& client): client(client) {}

    void handle_acpt_connection(const id_client_t& id_client) override;
    void handle_recv_close_connection() override;
    void handle_game_created(GameCreatedDTO dto) override;
    void handle_joined_match(ClientJoinedMatchDTO dto) override;
    void handle_recv_active_games(ActiveGamesDTO dto) override;
};


#endif
