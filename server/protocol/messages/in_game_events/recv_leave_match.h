#include "../server_message.h"

class RecvLeaveMatchMessage: public Message {
private:
    uint16_t id_player;

public:
    explicit RecvLeaveMatchMessage(uint16_t id_player);
    void run() override;
    ~RecvLeaveMatchMessage();
};
