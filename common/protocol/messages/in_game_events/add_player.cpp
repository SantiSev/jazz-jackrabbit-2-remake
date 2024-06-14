#include "add_player.h"


AddPlayerMessage::AddPlayerMessage(const AddPlayerDTO& dto): Message(ADD_PLAYER), dto(dto) {}


void AddPlayerMessage::run(MessageHandler& handler) { handler.handle_add_player(dto); }


void AddPlayerMessage::send_message(CommonProtocol& protocol) {
    protocol.send_add_player(header, dto);
}

AddPlayerMessage::~AddPlayerMessage() = default;
