#include "client_message_handler.h"

#include <iostream>

#include "client_thread_manager.h"

ClientMessageHandler::ClientMessageHandler(): send_message() {}

void ClientMessageHandler::send_command(command_t command) {
    CommandDTO dto;
    dto.id_player = id_player;
    dto.command = command;
    send_message.push(std::make_shared<RecvCommandMessage>(dto));
}

void ClientMessageHandler::handle_acpt_connection(const id_client_t& client_id) {
    this->id_client = client_id;
}

void ClientMessageHandler::handle_recv_close_connection() {
    //    client.close_connection(); // todo: falta implementar
}

void ClientMessageHandler::handle_joined_match(const ClientHasConnectedToMatchDTO& dto) {
    //    client.set_my_player_id(dto.id_player);
}

void ClientMessageHandler::handle_game_created(const ClientHasConnectedToMatchDTO& dto) {
    //    client.set_my_player_id(dto.id_player);
}

void ClientMessageHandler::handle_recv_active_games(const MatchInfoDTO& dto) {
    //    client.set_active_games(dto);
}

void ClientMessageHandler::handle_recv_game_state(const GameStateDTO& dto) {
    // client.set_game_state(dto);
}
