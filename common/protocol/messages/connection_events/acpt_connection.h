#ifndef TP_FINAL_MADE_FIRST_CONNECTION_H
#define TP_FINAL_MADE_FIRST_CONNECTION_H

#include <cstdint>
#include <string>

#include "../common_message.h"

class AcptConnection: public Message {
private:
    const id_client_t id_client;

public:
    explicit AcptConnection(uint16_t id_client);

    void run(MessageHandler& handler) override;

    void send_message(CommonProtocol& protocol) override;

    ~AcptConnection() override;
};

#endif
