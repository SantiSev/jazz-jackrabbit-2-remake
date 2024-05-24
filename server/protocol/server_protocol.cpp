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

const uint8_t ServerProtocol::recv_one_byte() {
    uint8_t one_byte;

    client.recvall(&one_byte, sizeof(one_byte), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return one_byte;
}

const uint16_t ServerProtocol::recv_two_bytes() {
    uint16_t two_bytes;

    client.recvall(&two_bytes, sizeof(two_bytes), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return ntohs(two_bytes);
}

const std::string ServerProtocol::recv_string() {
    uint8_t length;

    client.recvall(&length, sizeof(length), &was_closed);
    length = ntohs(length);

    std::vector<char> buf(length);
    client.recvall(buf.data(), length, &was_closed);

    std::string match_name(buf.begin(), buf.end());

    return match_name;
}

std::shared_ptr<RecvCommandMessage> ServerProtocol::recv_command() {
    const uint16_t id_player = recv_two_bytes();
    const uint8_t id_command = recv_one_byte();
    return std::make_shared<RecvCommandMessage>(id_player, id_command);
}

std::shared_ptr<RecvCheatCommandMessage> ServerProtocol::recv_cheat_command() {
    const uint16_t id_player = recv_two_bytes();
    const uint8_t id_cheat_command = recv_one_byte();
    return std::make_shared<RecvCheatCommandMessage>(id_player, id_cheat_command);
}

std::shared_ptr<RecvUnjoinMatchMessage> ServerProtocol::recv_unjoin_match() {
    const uint16_t id_player = recv_two_bytes();
    return std::make_shared<RecvUnjoinMatchMessage>(id_player);
}

std::shared_ptr<RecvCreateGameMessage> ServerProtocol::recv_create_game() {
    const uint16_t id_player = recv_two_bytes();
    std::string match_name = recv_string();
    return std::make_shared<RecvCreateGameMessage>(id_player, match_name);
}

std::shared_ptr<RecvJoinMatchMessage> ServerProtocol::recv_join_match() {
    const uint16_t id_player = recv_two_bytes();
    const uint16_t id_match = recv_two_bytes();
    const uint8_t player_character = recv_one_byte();
    return std::make_shared<RecvJoinMatchMessage>(id_player, id_match, player_character);
}

std::shared_ptr<Message> ServerProtocol::recv_message() {
    const uint16_t header = recv_two_bytes();

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
