#include "client_message_handler.h"

#include <iostream>

#include "../../common/protocol/messages/menu_events/recv_active_games.h"

#include "client_thread_manager.h"

ClientMessageHandler::ClientMessageHandler() {}

void ClientMessageHandler::send_command(command_t command) {
    CommandDTO dto{};
    dto.id_player = id_player;
    dto.command = command;
    send_message.push(std::make_shared<RecvCommandMessage>(dto));
}

void ClientMessageHandler::create_match(character_t character, uint8_t map_name,
                                        uint8_t max_players) {
    CreateGameDTO dto;
    dto.id_client = id_client;
    dto.character_selected = character;
    dto.map_name = character;
    dto.max_players = character;
    send_message.push(std::make_shared<RecvCreateGameMessage>(dto));
}

void ClientMessageHandler::join_match(id_match_t id_match, character_t character) {
    JoinMatchDTO dto;
    dto.id_client = id_client;
    dto.id_match = id_match;
    dto.player_character = character;
    send_message.push(std::make_shared<RecvJoinMatchMessage>(dto));
}

void ClientMessageHandler::quit() { send_message.push(std::make_shared<CloseConnectionMessage>()); }

void ClientMessageHandler::handle_acpt_connection(const id_client_t& client_id) {
    this->id_client = client_id;
}

void ClientMessageHandler::handle_recv_close_connection() {
    //    client.close_connection(); // todo: falta implementar
}

void ClientMessageHandler::handle_connected_to_match(const ClientHasConnectedToMatchDTO& dto) {
    send_message.push(std::make_shared<SendConnectedToGameMessage>(dto));
}

void ClientMessageHandler::handle_recv_active_games(const MatchInfoDTO& dto) {
    send_message.push(std::make_shared<RecvActiveGames>(dto));
}

void ClientMessageHandler::handle_recv_game_state(const GameStateDTO& dto) {
    game_state_q.push(std::make_shared<GameStateDTO>(dto));
}
