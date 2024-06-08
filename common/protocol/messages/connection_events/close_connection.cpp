#include "./close_connection.h"

CloseConnectionMessage::CloseConnectionMessage(const CloseConnectionDTO& closed_con_dto):
        Message(CLOSE_CONNECTION), dto(closed_con_dto) {}

void CloseConnectionMessage::run(MessageHandler& handler) {
    handler.handle_recv_close_connection(dto);
}

void CloseConnectionMessage::send_message(CommonProtocol& protocol) {
    protocol.send_close_connection(header);
}

CloseConnectionMessage::~CloseConnectionMessage() = default;
