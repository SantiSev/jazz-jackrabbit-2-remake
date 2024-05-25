#ifndef _SERVER_MESSAGE_H
#define _SERVER_MESSAGE_H

#include <cstdint>
#include <string>

class Message {
public:
    Message();
    virtual void run() = 0;
    ~Message();
};

#endif
