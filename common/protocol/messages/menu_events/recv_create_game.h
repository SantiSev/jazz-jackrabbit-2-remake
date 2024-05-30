#ifndef _RECV_CREATE_GAME_H
#define _RECV_CREATE_GAME_H
#include <cstdint>
#include <string>

#define RECV_CREATE_GAME 0x0201

#include "../common_message.h"

class RecvCreateGameMessage: public Message {
private:
    uint16_t header = RECV_CREATE_GAME;
    uint16_t id_player;
    std::string match_name;

public:
    RecvCreateGameMessage(uint16_t id_player, const std::string& match_name);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvCreateGameMessage();
};

#endif
