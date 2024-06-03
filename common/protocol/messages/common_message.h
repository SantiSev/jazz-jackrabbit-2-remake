#ifndef _COMMON_MESSAGE_H
#define _COMMON_MESSAGE_H

#include <cstdint>
#include <memory>

#include "../common_protocol.h"

class CommonProtocol;
class ClientProtocol;
class MatchesManager;
class Match;

class Message {
protected:
    const uint16_t header;

public:
    explicit Message(const uint16_t header);
    uint16_t get_header() const;
    virtual void send_message(CommonProtocol& protocol) = 0;
    virtual void run(ClientProtocol& client_protocol) {}
    virtual void run(MatchesManager& matches_manager) {}
    virtual void run(Match& match) {}
    virtual void run();
    virtual ~Message();
};

#endif
