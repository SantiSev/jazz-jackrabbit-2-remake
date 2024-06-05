#ifndef TP_FINAL_MANAGER_MESSAGE_HANDLER_H
#define TP_FINAL_MANAGER_MESSAGE_HANDLER_H

#include "../../common/protocol/messages/message_handler.h"
//#include "../../server/game_logic/matches_manager.h"

class MatchesManager;

class MatchesManagerMessageHandler: public MessageHandler {
private:
    MatchesManager& matches_manager;

public:
    explicit MatchesManagerMessageHandler(MatchesManager& matches_manager):
            matches_manager(matches_manager) {}

    void handle_recv_create_game(const CreateGameDTO& dto) override;

    void handle_recv_join_match(const JoinMatchDTO& dto) override;

    void handle_request_active_games(const RequestActiveGamesDTO& dto) override;
};


#endif