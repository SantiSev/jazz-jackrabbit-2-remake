#include "./send_finish_match.h"

SendFinishMatchMessage::SendFinishMatchMessage() {}

void SendFinishMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_finish_match();
}

void SendFinishMatchMessage::run() {}

SendFinishMatchMessage::~SendFinishMatchMessage() {}
