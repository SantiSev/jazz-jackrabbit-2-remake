#include "./send_game_created.h"

SendGameCreatedMessage::SendGameCreatedMessage() {}

void SendGameCreatedMessage::run() {}

void SendGameCreatedMessage::send_message(CommonProtocol& protocol) {
  protocol.send_game_created();
}

SendGameCreatedMessage::~SendGameCreatedMessage() {}
