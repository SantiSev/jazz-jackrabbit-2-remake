#ifndef _SEND_GAME_STATE_H
#define _SEND_GAME_STATE_H

#include "../common_message.h"

#define SEND_GAME_STATE 0x0100

class SendGameStateMessage: public Message {
private:
    GameStateDTO game_state;

public:
    explicit SendGameStateMessage(const GameStateDTO& game_state);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~SendGameStateMessage() override;
};

#endif
