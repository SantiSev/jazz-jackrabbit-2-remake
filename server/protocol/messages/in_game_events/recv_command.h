#include "../server_message.h"

class RecvCommandMessage: public Message {
private:
    uint16_t id_player;
    uint8_t id_command;

public:
    RecvCommandMessage(uint16_t id_player, uint8_t id_command);
    void run() override;
    ~RecvCommandMessage();
};
