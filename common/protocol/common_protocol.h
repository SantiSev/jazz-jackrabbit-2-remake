#ifndef _COMMON_PROTOCOL_H
#define _COMMON_PROTOCOL_H
#include <cstdint>
#include <string>

#include "../common_socket.h"

#define CLOSE_CONNECTION 0x0000

#define SEND_GAME_STATE 0x0100
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_LEAVE_MATCH 0x0103
#define SEND_FINISH_MATCH 0x0104

#define SEND_ACTIVE_GAMES 0x0200
#define RECV_CREATE_GAME 0x0201
#define SEND_GAME_CREATED 0x0202
#define RECV_JOIN_MATCH 0x0203

class CommonProtocol {
protected:
    Socket skt;
    bool was_closed;

    const uint8_t recv_one_byte();
    const uint16_t recv_two_bytes();
    const std::string recv_string();

public:
    explicit CommonProtocol(Socket&& skt);
    CommonProtocol(const std::string& hostname, const std::string& servname);
    ~CommonProtocol();

    void force_shutdown();
};

#endif
