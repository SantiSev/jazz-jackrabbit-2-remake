#ifndef _RECV_JOIN_MATCH_H
#define _RECV_JOIN_MATCH_H

#include <cstdint>

#define RECV_JOIN_MATCH 0x0203

#include "../common_message.h"

class RecvJoinMatchMessage: public Message {
private:
    uint16_t header = RECV_JOIN_MATCH;
    uint16_t id_player;
    uint16_t id_match;
    uint8_t player_character;

public:
    RecvJoinMatchMessage(uint16_t id_player, uint16_t id_match, uint8_t player_character);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvJoinMatchMessage();
};

#endif
