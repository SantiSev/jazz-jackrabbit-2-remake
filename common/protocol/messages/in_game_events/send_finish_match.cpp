#include "./send_finish_match.h"

SendFinishMatchMessage::SendFinishMatchMessage(): Message(SEND_FINISH_MATCH) {}


void SendFinishMatchMessage::run(MessageHandler& handler) {}

void SendFinishMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_finish_match(header);
}

SendFinishMatchMessage::~SendFinishMatchMessage() = default;
