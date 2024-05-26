#include "../common_message.h"

class SendFinishMatchMessage: public Message {
public:
    SendFinishMatchMessage();
    void run() override;
    ~SendFinishMatchMessage();
};
