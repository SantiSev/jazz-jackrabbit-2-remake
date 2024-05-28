#ifndef _CLOSING_CONNECTION_H
#define _CLOSING_CONNECTION_H

#include "../common_message.h"

class CloseConnectionMessage: public Message {
public:
    CloseConnectionMessage();
    void run() override;
    ~CloseConnectionMessage();
};

#endif
