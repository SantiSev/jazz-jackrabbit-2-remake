#ifndef TP_FINAL_MESSAGE_H
#define TP_FINAL_MESSAGE_H
#include <cstdio>

//#include "snapshot.h"

class MessageTest {
private:
    size_t id;

public:
    explicit MessageTest(size_t id);

    //    explicit Message(const Snapshot& snapshot);

    size_t get_id() const;
    void run();
};


#endif
