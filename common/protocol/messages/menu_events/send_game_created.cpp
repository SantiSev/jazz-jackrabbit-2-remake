#include "./send_game_created.h"

#include "../../../../client/protocol/client_protocol.h"

SendGameCreatedMessage::SendGameCreatedMessage(uint16_t id_player): player_id(id_player) {}

void SendGameCreatedMessage::run() {}

void SendGameCreatedMessage::run(ClientProtocol& client_protocol) {
    client_protocol.set_my_player_id(player_id);
}

void SendGameCreatedMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_created(player_id);
}
SendGameCreatedMessage::~SendGameCreatedMessage() = default;
