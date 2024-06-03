#ifndef _RECV_CHEAT_COMMAND_H
#define _RECV_CHEAT_COMMAND_H

#include "../common_message.h"

#define RECV_CHEAT_COMMAND 0x0102

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
