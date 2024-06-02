#ifndef _COMMON_PROTOCOL_H
#define _COMMON_PROTOCOL_H
#include <cstdint>
#include <string>
#include <vector>

#include "../../common/common_socket.h"
#include "./messages/common_dto.h"

#define CLOSE_CONNECTION 0x0000
#define MADE_CONNECTION 0x0001

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
    virtual void send_close_connection() = 0;
    virtual void send_game_state() = 0;
    virtual void send_finish_match() = 0;
    virtual void send_active_games(uint8_t length, std::vector<MatchDTO>& matches) = 0;
    virtual void send_game_created(uint16_t id_player) = 0;
    virtual void send_first_connection(uint16_t id_client) = 0;
    virtual void force_shutdown();
    ~CommonProtocol();
};

#endif
