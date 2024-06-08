#ifndef TP_FINAL_MATCH_MESSAGE_HANDLER_H
#define TP_FINAL_MATCH_MESSAGE_HANDLER_H

#include "../../common/protocol/common_dto.h"
#include "../../common/protocol/messages/connection_events/close_connection.h"
#include "../../common/protocol/messages/message_handler.h"

class Match;

class MatchMessageHandler: public MessageHandler {
private:
    Match& match;

public:
    explicit MatchMessageHandler(Match& match): match(match) {}

    void handle_recv_command(const CommandDTO& command) override;

    void handle_recv_close_connection(const CloseConnectionDTO& dto) override;

    void handle_recv_cheat_command(const CheatCommandDTO& cheat_command);
};


#endif
