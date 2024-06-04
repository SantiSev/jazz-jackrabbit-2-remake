#ifndef TP_FINAL_SEND_GAME_JOINED_H
#define TP_FINAL_SEND_GAME_JOINED_H

#include "../common_message.h"

class SendGameJoined: public Message {
private:
    ClientJoinedMatchDTO game_joined;

public:
    explicit SendGameJoined(const ClientJoinedMatchDTO& game_joined);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~SendGameJoined() override;
};


#endif
