#ifndef TP_FINAL_CLIENT_MESSAGE_HANDLER_H
#define TP_FINAL_CLIENT_MESSAGE_HANDLER_H

#include <iostream>
#include <memory>

#include "../../common/protocol/messages/common_message.h"
#include "../../common/protocol/messages/menu_events/recv_active_games.h"
#include "../../common/protocol/messages/message_handler.h"
#include "../game_objects/player.h"

#include "client_thread_manager.h"

class Client;

class ClientMessageHandler: public MessageHandler {
private:
    Client& client;

public:
    Queue<std::shared_ptr<Message>> send_message;
    Queue<std::shared_ptr<GameStateDTO>> game_state_q;

    explicit ClientMessageHandler(Client& client);

    void send_command(command_t command);
    void create_match(character_t character, map_list_t map_name, uint8_t max_players);
    void join_match(id_match_t id_match, character_t character);
    void quit();

    void handle_acpt_connection(const id_client_t& id_client) override;
    void handle_recv_close_connection(const CloseConnectionDTO& dto) override;
    void handle_connected_to_match(const ClientHasConnectedToMatchDTO& dto) override;
    void handle_recv_active_games(const MatchInfoDTO& dto) override;
    void handle_recv_game_state(const GameStateDTO& dto) override;
    void handle_recv_finish_match() override;
};


#endif
