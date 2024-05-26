#include "../client_message.h"

class CloseConnectionMessage: public Message {
public:
    CloseConnectionMessage();
    void run() override;
    ~CloseConnectionMessage();
};
