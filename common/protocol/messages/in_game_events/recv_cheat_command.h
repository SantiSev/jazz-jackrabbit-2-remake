#ifndef _RECV_CHEAT_COMMAND_H
#define _RECV_CHEAT_COMMAND_H

#include <cstdint>

#include "../common_message.h"

class RecvCheatCommandMessage: public Message {
private:
    CheatCommandDTO cheat_command;

public:
    explicit RecvCheatCommandMessage(CheatCommandDTO& cheat_command);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvCheatCommandMessage();
};

#endif
