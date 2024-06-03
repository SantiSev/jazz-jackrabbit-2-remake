#ifndef _SEND_FINISH_MATCH_H
#define _SEND_FINISH_MATCH_H

#include "../common_message.h"

#define SEND_FINISH_MATCH 0x0104

class SendFinishMatchMessage: public Message {
private:
    FinishMatchDTO finish_match;

public:
    explicit SendFinishMatchMessage(FinishMatchDTO& finish_match);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~SendFinishMatchMessage();
};

#endif
