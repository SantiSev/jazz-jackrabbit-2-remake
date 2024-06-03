#include "./send_game_created.h"

#include "../../../../client/protocol/client_protocol.h"

SendGameCreatedMessage::SendGameCreatedMessage(GameCreatedDTO& game_created):
        Message(SEND_GAME_CREATED), game_created(game_created) {}

void SendGameCreatedMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_created(header, game_created);
}

void SendGameCreatedMessage::run(ClientProtocol& client_protocol) {
    client_protocol.set_my_player_id(game_created.id_player);
}

void SendGameCreatedMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_created(header, game_created);
}

SendGameCreatedMessage::~SendGameCreatedMessage() = default;
