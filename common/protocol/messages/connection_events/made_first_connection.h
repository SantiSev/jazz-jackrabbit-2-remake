#ifndef TP_FINAL_MADE_FIRST_CONNECTION_H
#define TP_FINAL_MADE_FIRST_CONNECTION_H

#include <cstdint>
#include <string>

#include "../common_message.h"

#define MADE_CONNECTION 0x0001

class MadeFirstConnection: public Message {

private:
    const uint16_t header = MADE_CONNECTION;
    uint16_t id_client;

public:
    explicit MadeFirstConnection(uint16_t client_id);
    void run(ClientProtocol& client_protocol) override;
    void run() override;

    void send_message(CommonProtocol& protocol) override;

    ~MadeFirstConnection() override;
};

#endif
