#include "../server_message.h"

class RecvJoinMatchMessage: public Message {
private:
    uint16_t id_player;
    uint16_t id_match;
    uint8_t player_character;

public:
    RecvJoinMatchMessage(uint16_t id_player, uint16_t id_match, uint8_t player_character);
    void run() override;
    ~RecvJoinMatchMessage();
};
