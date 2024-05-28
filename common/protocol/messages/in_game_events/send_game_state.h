#include "../common_message.h"

class SendGameStateMessage: public Message {
public:
    SendGameStateMessage();
    void run() override;
    ~SendGameStateMessage();
};
