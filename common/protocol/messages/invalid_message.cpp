#include "./invalid_message.h"

InvalidMessage::InvalidMessage() {}

void InvalidMessage::run() {}

void InvalidMessage::send_message(CommonProtocol& protocol) {
    // protocol.send_game_created();
}

InvalidMessage::~InvalidMessage() {}
