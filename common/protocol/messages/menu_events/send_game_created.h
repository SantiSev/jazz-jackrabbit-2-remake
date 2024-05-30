#ifndef _SEND_GAME_CREATED_H
#define _SEND_GAME_CREATED_H

#include "../common_message.h"

class SendGameCreatedMessage: public Message {
public:
    SendGameCreatedMessage();
    void run() override;
    ~SendGameCreatedMessage();
};

#endif
