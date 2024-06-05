#include "client_message_handler.h"

#include <iostream>

#include "client_thread_manager.h"

void ClientMessageHandler::handle_acpt_connection(const id_client_t& id_client) {
    client.set_my_client_id(id_client);
}

void ClientMessageHandler::handle_recv_close_connection() {
    //    client.close_connection(); // todo: falta implementar
}

void ClientMessageHandler::handle_joined_match(ClientJoinedMatchDTO dto) {
    client.set_my_client_id(dto.id_client);
    client.set_my_player_id(dto.id_player);
}

void ClientMessageHandler::handle_game_created(GameCreatedDTO dto) {
    client.set_my_player_id(dto.id_player);
}

void ClientMessageHandler::handle_recv_active_games(ActiveGamesDTO dto) {
    client.set_active_games(dto);
}


// void ClientMessageHandler::handle_message(const std::shared_ptr<Message>& message) {
//     const uint16_t header = message->get_header();
//     switch (header) {
//         case SEND_FINISH_MATCH:
//             handle_finish_match(static_pointer_cast<SendFinishMatchMessage>(message));
//             break;
//         case SEND_GAME_STATE:
//             handle_game_state(static_pointer_cast<SendGameStateMessage>(message));
//             break;
//         case SEND_ACTIVE_GAMES:
//             handle_active_games(static_pointer_cast<SendActiveGamesMessage>(message));
//             break;
//         case SEND_GAME_CREATED:
//             handle_game_created(static_pointer_cast<SendGameCreatedMessage>(message));
//             break;
//         case ACPT_CONNECTION:
//             handle_acpt_connection(static_pointer_cast<AcptConnection>(message));
//             break;
//         default:
//             std::cout << "Invalid message" << std::endl;
//     }
// }
