#include "./invalid_message.h"

InvalidMessage::InvalidMessage(): Message(NULL_MESSAGE) {}


void InvalidMessage::run(MessageHandler& handler) {}

void InvalidMessage::send_message(CommonProtocol& protocol) {}

InvalidMessage::~InvalidMessage() = default;
