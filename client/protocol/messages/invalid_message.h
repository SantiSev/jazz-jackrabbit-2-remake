#include "./client_message.h"

class InvalidMessage: public Message {
public:
    InvalidMessage();
    void run() override;
    ~InvalidMessage();
};
