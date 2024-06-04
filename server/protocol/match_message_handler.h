#ifndef TP_FINAL_MATCH_MESSAGE_HANDLER_H
#define TP_FINAL_MATCH_MESSAGE_HANDLER_H

#include "../../common/protocol/common_dto.h"
#include "../../common/protocol/messages/message_handler.h"

class Match;

class MatchMessageHandler: public MessageHandler {
private:
    Match& match;

public:
    explicit MatchMessageHandler(Match& match): match(match) {}
};


#endif
