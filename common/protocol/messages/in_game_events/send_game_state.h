#ifndef _SEND_GAME_STATE_H
#define _SEND_GAME_STATE_H

#include <cstdint>
#include <vector>

#include "../../../message/snapshot.h"
#include "../../common_protocol.h"
#include "../common_message.h"

#define SEND_GAME_STATE 0x0100

class SendGameStateMessage: public Message {
private:
    uint16_t header = SEND_GAME_STATE;
    int match_seconds = 0;
    int match_minutes = 0;
    std::vector<Player> players;
    std::vector<Enemies> enemies;

public:
    SendGameStateMessage();

    explicit SendGameStateMessage(const Snapshot& snapshot);

    void run() override;

    void send_message(CommonProtocol& protocol) override;

    ~SendGameStateMessage() override;
};

#endif
