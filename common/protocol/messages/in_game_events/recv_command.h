#ifndef _RECV_COMMAND_H
#define _RECV_COMMAND_H
#include <cstdint>

#include "../common_message.h"

#define RECV_COMMAND 0x0101

class RecvCommandMessage: public Message {
private:
    uint16_t header = RECV_COMMAND;
    uint16_t id_player;
    uint8_t id_command;

public:
    RecvCommandMessage(const uint16_t& id_player, const uint8_t& id_command);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvCommandMessage();
};

#endif
