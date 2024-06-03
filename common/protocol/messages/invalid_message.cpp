#include "./invalid_message.h"

InvalidMessage::InvalidMessage(): Message(0xFFFF) {}

void InvalidMessage::run() {}

void InvalidMessage::send_message(CommonProtocol& protocol) {}

InvalidMessage::~InvalidMessage() {}
