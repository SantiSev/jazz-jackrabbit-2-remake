#include "../client_message.h"

class SendActiveGamesMessage: public Message {
public:
    SendActiveGamesMessage();
    void run() override;
    ~SendActiveGamesMessage();
};
