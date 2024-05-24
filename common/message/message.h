#ifndef TP_FINAL_MESSAGE_H
#define TP_FINAL_MESSAGE_H
#include <cstdio>

#include "../../server/server_eventloop.h"

class Message {
private:
    size_t id;

public:
    explicit Message(size_t id);

    size_t get_id() const;
    void run(ServerEventloop* eventloop);
};


#endif
