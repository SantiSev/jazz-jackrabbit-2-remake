#include "./server_protocol.h"

#include <vector>

#include <arpa/inet.h>

#define CLOSE_CONNECTION 0x0000
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_UNJOIN_MATCH 0x0103
#define RECV_CREATE_GAME 0x0201
#define RECV_JOIN_MATCH 0x0203

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {}

const uint16_t ServerProtocol::recv_id_player() {
    uint16_t id_player;

    client.recvall(&id_player, sizeof(id_player), &was_closed);
    id_player = ntohs(id_player);
    if (was_closed)
        return CLOSE_CONNECTION;

    return id_player;
}

const uint8_t ServerProtocol::recv_id_command() {
    uint8_t id_command;

    client.recvall(&id_command, sizeof(id_command), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return id_command;
}

const uint8_t ServerProtocol::recv_id_cheat_command() {
    uint8_t id_cheat_command;

    client.recvall(&id_cheat_command, sizeof(id_cheat_command), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return id_cheat_command;
}

const uint16_t ServerProtocol::recv_header() {
    uint16_t header;

    client.recvall(&header, sizeof(header), &was_closed);
    header = ntohs(header);
    if (was_closed)
        return CLOSE_CONNECTION;

    return header;
}

const std::string ServerProtocol::recv_match_name() {
    uint8_t length;

    client.recvall(&length, sizeof(length), &was_closed);
    length = ntohs(length);

    std::vector<char> buf(length);
    client.recvall(buf.data(), length, &was_closed);

    std::string match_name(buf.begin(), buf.end());

    return match_name;
}

const uint16_t ServerProtocol::recv_id_match() {
    uint16_t id_match;

    client.recvall(&id_match, sizeof(id_match), &was_closed);
    id_match = ntohs(id_match);
    if (was_closed)
        return CLOSE_CONNECTION;

    return id_match;
}

const uint8_t ServerProtocol::recv_player_character() {
    uint8_t player_character;

    client.recvall(&player_character, sizeof(player_character), &was_closed);

    return player_character;
}

std::shared_ptr<RecvCommandMessage> ServerProtocol::recv_command() {
    const uint16_t id_player = recv_id_player();
    const uint8_t id_command = recv_id_command();
    return std::make_shared<RecvCommandMessage>(id_player, id_command);
}

std::shared_ptr<RecvCheatCommandMessage> ServerProtocol::recv_cheat_command() {
    const uint16_t id_player = recv_id_player();
    const uint8_t id_cheat_command = recv_id_cheat_command();
    return std::make_shared<RecvCheatCommandMessage>(id_player, id_cheat_command);
}

std::shared_ptr<RecvUnjoinMatchMessage> ServerProtocol::recv_unjoin_match() {
    const uint16_t id_player = recv_id_player();
    return std::make_shared<RecvUnjoinMatchMessage>(id_player);
}

std::shared_ptr<RecvCreateGameMessage> ServerProtocol::recv_create_game() {
    const uint16_t id_player = recv_id_player();
    std::string match_name = recv_match_name();
    return std::make_shared<RecvCreateGameMessage>(id_player, match_name);
}

std::shared_ptr<RecvJoinMatchMessage> ServerProtocol::recv_join_match() {
    const uint16_t id_player = recv_id_player();
    const uint16_t id_match = recv_id_match();
    const uint8_t player_character = recv_player_character();
    return std::make_shared<RecvJoinMatchMessage>(id_player, id_match, player_character);
}

std::shared_ptr<Message> ServerProtocol::recv_message() {
    const uint16_t header = recv_header();

    switch (header) {
        case CLOSE_CONNECTION:
            return std::make_shared<CloseConnectionMessage>();
        case RECV_COMMAND:
            return recv_command();
        case RECV_CHEAT_COMMAND:
            return recv_cheat_command();
        case RECV_UNJOIN_MATCH:
            return recv_unjoin_match();
        case RECV_CREATE_GAME:
            return recv_create_game();
        case RECV_JOIN_MATCH:
            return recv_join_match();
        default:
            return std::make_shared<InvalidMessage>();
    }
}

bool ServerProtocol::is_closed() const { return was_closed; }
