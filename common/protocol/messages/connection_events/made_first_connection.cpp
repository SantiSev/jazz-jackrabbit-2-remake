#include "made_first_connection.h"

#include "../../../../client/protocol/client_protocol.h"

MadeFirstConnection::MadeFirstConnection(uint16_t client_id) { this->id_client = client_id; }

void MadeFirstConnection::run(ClientProtocol& client_protocol) {
    client_protocol.set_my_client_id(id_client);
}

void MadeFirstConnection::run() {}

void MadeFirstConnection::send_message(CommonProtocol& protocol) {
    protocol.send_first_connection(id_client);
}
MadeFirstConnection::~MadeFirstConnection() {}
