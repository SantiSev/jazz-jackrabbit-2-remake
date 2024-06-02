#ifndef _COMMON_MESSAGE_H
#define _COMMON_MESSAGE_H

#include <cstdint>
#include <memory>

#include "../common_protocol.h"

class ClientProtocol;
class MatchesManager;
class Match;

class Message {
private:
    uint16_t header;

public:
    Message();
    uint16_t return_header() const { return header; }
    virtual void send_message(CommonProtocol& protocol) = 0;
    virtual void run(ClientProtocol& client_protocol) {}
    virtual void run(MatchesManager& matches_manager) {}
    virtual void run(Match& match) {}
    virtual void run();
    virtual ~Message();
};

#endif
