#ifndef TP_FINAL_RECV_ACTIVE_GAMES_H
#define TP_FINAL_RECV_ACTIVE_GAMES_H

#include "../common_message.h"

class RecvActiveGames: public Message {
private:
    MatchInfoDTO active_games;

public:
    explicit RecvActiveGames(const MatchInfoDTO& dto);

    void run(MessageHandler& handler) override;

    void send_message(CommonProtocol& protocol) override;

    ~RecvActiveGames() override;
};


#endif
