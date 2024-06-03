#include "./close_connection.h"

CloseConnectionMessage::CloseConnectionMessage(): Message(CLOSE_CONNECTION) {}

void CloseConnectionMessage::run() {}

void CloseConnectionMessage::send_message(CommonProtocol& protocol) {
    protocol.send_close_connection(header);
}

CloseConnectionMessage::~CloseConnectionMessage() {}
