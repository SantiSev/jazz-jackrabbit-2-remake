#ifndef TP_FINAL_MESSAGE_H
#define TP_FINAL_MESSAGE_H
#include <cstdio>

class Message {
private:
    size_t id;

public:
    explicit Message(size_t id);

    size_t get_id() const;
    void run();
};


#endif
