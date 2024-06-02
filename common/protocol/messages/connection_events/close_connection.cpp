#include "./close_connection.h"

#include "../../../../client/protocol/client_protocol.h"

CloseConnectionMessage::CloseConnectionMessage() {}

void CloseConnectionMessage::run() {}

void CloseConnectionMessage::run(ClientProtocol& client_protocol) {}

void CloseConnectionMessage::send_message(CommonProtocol& protocol) {
    protocol.send_close_connection();
}

CloseConnectionMessage::~CloseConnectionMessage() {}
