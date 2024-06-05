#ifndef TP_FINAL_CLIENT_MESSAGE_HANDLER_H
#define TP_FINAL_CLIENT_MESSAGE_HANDLER_H

#include <memory>

#include "../../common/protocol/messages/common_message.h"
#include "../../common/protocol/messages/message_handler.h"
#include "../game_objects/player.h"

class ClientThreadManager;

class ClientMessageHandler: public MessageHandler {
private:
    id_client_t id_client = 0;
    id_player_t id_player = 0;

public:
    Queue<std::shared_ptr<Message>> send_message;
    ClientMessageHandler();

    void send_command(command_t command);

    void handle_acpt_connection(const id_client_t& id_client) override;
    void handle_recv_close_connection() override;
    void handle_game_created(const GameCreatedDTO& dto) override;
    void handle_joined_match(const ClientJoinedMatchDTO& dto) override;
    void handle_recv_active_games(const MatchInfoDTO& dto) override;
};


#endif
