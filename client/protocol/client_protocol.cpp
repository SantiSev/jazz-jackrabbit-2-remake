#include "./client_protocol.h"

#include <vector>

#include <arpa/inet.h>

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

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        server(hostname.c_str(), servname.c_str()), was_closed(false) {}

void ClientProtocol::send_command(uint16_t id_player, uint8_t id_command) {
    uint16_t header = htons(RECV_COMMAND);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(header), &was_closed);
    if (was_closed)
        return;

    server.sendall(&id_command, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_cheat_command(uint16_t id_player, uint8_t id_cheat_command) {
    uint16_t header = htons(RECV_CHEAT_COMMAND);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(header), &was_closed);
    if (was_closed)
        return;

    server.sendall(&id_cheat_command, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_leave_match() {
    uint16_t header = htons(RECV_LEAVE_MATCH);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_create_game() {
    uint16_t header = htons(RECV_CREATE_GAME);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_join_match() {
    uint16_t header = htons(RECV_JOIN_MATCH);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

ClientProtocol::~ClientProtocol() {}
