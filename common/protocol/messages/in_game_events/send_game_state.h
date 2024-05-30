#ifndef _SEND_GAME_STATE_H
#define _SEND_GAME_STATE_H

#include "../common_message.h"

class SendGameStateMessage: public Message {
public:
    SendGameStateMessage();
    void run() override;
    ~SendGameStateMessage();
};

#endif
