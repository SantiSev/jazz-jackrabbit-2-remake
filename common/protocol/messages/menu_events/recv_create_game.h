#ifndef _RECV_CREATE_GAME_H
#define _RECV_CREATE_GAME_H
#include <cstdint>
#include <string>

#define RECV_CREATE_GAME 0x0201

#include "../common_message.h"
//#include "../../../../server/game_logic/matches_manager.h"

class RecvCreateGameMessage: public Message {
private:
    uint16_t header = RECV_CREATE_GAME;
    uint16_t id_client;
    std::string match_name;

public:
    RecvCreateGameMessage(uint16_t client_id, const std::string& match_name);
    //    void run(MatchesManager& matches_manager) override;
    void run() override;
    void send_message(CommonProtocol& protocol) override;

    ~RecvCreateGameMessage();
};

#endif
