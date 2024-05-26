#include "../common_message.h"

class SendGameCreatedMessage: public Message {
public:
    SendGameCreatedMessage();
    void run() override;
    ~SendGameCreatedMessage();
};
