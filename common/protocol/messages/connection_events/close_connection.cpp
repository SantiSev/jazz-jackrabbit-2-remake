#include "./close_connection.h"

CloseConnectionMessage::CloseConnectionMessage(): Message(CLOSE_CONNECTION) {}

void CloseConnectionMessage::run() {}

void CloseConnectionMessage::run(ClientProtocol& client_protocol) {}

void CloseConnectionMessage::send_message(CommonProtocol& protocol) {
    protocol.send_close_connection(header);
}

CloseConnectionMessage::~CloseConnectionMessage() {}
