#ifndef _CLIENT_MESSAGE_H
#define _CLIENT_MESSAGE_H

class Message {
public:
    Message();
    virtual void run() = 0;
    ~Message();
};

#endif
