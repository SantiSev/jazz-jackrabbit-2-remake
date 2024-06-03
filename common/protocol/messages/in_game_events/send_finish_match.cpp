#include "./send_finish_match.h"

SendFinishMatchMessage::SendFinishMatchMessage(FinishMatchDTO& finish_match):
        Message(SEND_FINISH_MATCH), finish_match(finish_match) {}


void SendFinishMatchMessage::run() {}

void SendFinishMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_finish_match(header, finish_match);
}

SendFinishMatchMessage::~SendFinishMatchMessage() {}
