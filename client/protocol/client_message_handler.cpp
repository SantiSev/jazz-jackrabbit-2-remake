#include "client_message_handler.h"

#include <iostream>

#include "client_thread_manager.h"

void ClientMessageHandler::handle_acpt_connection(const id_client_t& id_client) {
    client.set_my_client_id(id_client);
}

void ClientMessageHandler::handle_recv_close_connection() {
    //    client.close_connection(); // todo: falta implementar
}

void ClientMessageHandler::handle_joined_match(const ClientHasConnectedToMatchDTO& dto) {
    client.set_my_player_id(dto.id_player);
}

void ClientMessageHandler::handle_game_created(const ClientHasConnectedToMatchDTO& dto) {
    client.set_my_player_id(dto.id_player);
}

void ClientMessageHandler::handle_recv_active_games(const MatchInfoDTO& dto) {
    client.set_active_games(dto);
}

void ClientMessageHandler::handle_recv_game_state(const GameStateDTO& dto) {
    // client.set_game_state(dto);
}
