#ifndef _RECV_CREATE_GAME_H
#define _RECV_CREATE_GAME_H

#include <cstdint>
#include <string>

#include "../../common_dto.h"
#include "../common_message.h"

class RecvCreateGameMessage: public Message {
private:
    CreateGameDTO create_game;

public:
    explicit RecvCreateGameMessage(CreateGameDTO& create_game);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvCreateGameMessage();
};

#endif
