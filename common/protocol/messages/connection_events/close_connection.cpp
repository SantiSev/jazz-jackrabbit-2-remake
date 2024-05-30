#include "./close_connection.h"

CloseConnectionMessage::CloseConnectionMessage() {}

void CloseConnectionMessage::run() {}

void CloseConnectionMessage::send_message(CommonProtocol& protocol) {
  protocol.send_close_connection();
}

CloseConnectionMessage::~CloseConnectionMessage() {}
