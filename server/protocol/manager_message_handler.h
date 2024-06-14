#ifndef TP_FINAL_MANAGER_MESSAGE_HANDLER_H
#define TP_FINAL_MANAGER_MESSAGE_HANDLER_H

#include <memory>

#include "../../common/common_queue.h"
#include "../../common/protocol/messages/common_message.h"
#include "../../common/protocol/messages/message_handler.h"
//#include "../../server/game_logic/matches_manager.h"

class MatchesManager;

class MatchesManagerMessageHandler: public MessageHandler {
private:
    MatchesManager& matches_manager;

public:
    Queue<std::shared_ptr<Message>>& lobby_queue;

    MatchesManagerMessageHandler(MatchesManager& matches_manager,
                                 Queue<std::shared_ptr<Message>>& lobby_queue);

    void handle_recv_create_game(const CreateGameDTO& dto) override;

    void handle_recv_join_match(const JoinMatchDTO& dto) override;

    void handle_request_active_games(const RequestActiveGamesDTO& dto) override;

    void handle_recv_close_connection(const CloseConnectionDTO& dto) override;

    void handle_recv_command(const CommandDTO& command) override;
};


#endif
