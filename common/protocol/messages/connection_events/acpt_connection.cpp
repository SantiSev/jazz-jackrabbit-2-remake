#include "acpt_connection.h"

AcptConnection::AcptConnection(uint16_t client_id):
        Message(ACPT_CONNECTION), id_client(client_id) {}


void AcptConnection::run(MessageHandler& handler) { handler.handle_acpt_connection(id_client); }
void AcptConnection::send_message(CommonProtocol& protocol) {
    protocol.send_acpt_connection(header, id_client);
}

AcptConnection::~AcptConnection() = default;
