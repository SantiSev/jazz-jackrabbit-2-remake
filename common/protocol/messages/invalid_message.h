#include "./common_message.h"

class InvalidMessage: public Message {
public:
    InvalidMessage();
    void run() override;
    ~InvalidMessage();
};
