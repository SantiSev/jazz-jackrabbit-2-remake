#include "./close_connection.h"

CloseConnectionMessage::CloseConnectionMessage(): Message(CLOSE_CONNECTION) {}

void CloseConnectionMessage::run(MessageHandler& handler) {
    handler.handle_recv_close_connection();
}

void CloseConnectionMessage::send_message(CommonProtocol& protocol) {
    protocol.send_close_connection(header);
}

CloseConnectionMessage::~CloseConnectionMessage() = default;
