#ifndef _RECV_CHEAT_COMMAND_H
#define _RECV_CHEAT_COMMAND_H
#include <cstdint>

#include "../common_message.h"

class RecvCheatCommandMessage: public Message {
private:
    uint16_t id_player;
    uint8_t id_cheat_command;

public:
    RecvCheatCommandMessage(uint16_t id_player, uint8_t id_cheat_command);
    void run() override;
    ~RecvCheatCommandMessage();
};

#endif
