#ifndef _SEND_FINISH_MATCH_H
#define _SEND_FINISH_MATCH_H

#include "../common_message.h"

class SendFinishMatchMessage: public Message {
public:
    SendFinishMatchMessage();
    void run() override;
    ~SendFinishMatchMessage();
};

#endif
