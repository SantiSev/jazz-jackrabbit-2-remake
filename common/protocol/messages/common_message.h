#ifndef _COMMON_MESSAGE_H
#define _COMMON_MESSAGE_H

class Message {
public:
    Message();
    virtual void run();
    virtual ~Message();
};

#endif
