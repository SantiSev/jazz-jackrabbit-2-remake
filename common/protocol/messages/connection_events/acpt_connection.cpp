#include "acpt_connection.h"

#include "../../../../client/protocol/client_protocol.h"

AcptConnection::AcptConnection(uint16_t client_id):
        Message(ACPT_CONNECTION), id_client(client_id) {}

void AcptConnection::run(ClientProtocol& client_protocol) {
    client_protocol.set_my_client_id(id_client);
}

void AcptConnection::run() {}

void AcptConnection::send_message(CommonProtocol& protocol) {
    protocol.send_acpt_connection(header, id_client);
}
AcptConnection::~AcptConnection() {}
