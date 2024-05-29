#include "./server_protocol.h"

#include <vector>

#include <arpa/inet.h>

ServerProtocol::ServerProtocol(Socket&& skt): CommonProtocol(std::move(skt)) {}

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

std::shared_ptr<RecvLeaveMatchMessage> ServerProtocol::recv_leave_match() {
    const uint16_t id_player = recv_two_bytes();
    return std::make_shared<RecvLeaveMatchMessage>(id_player);
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
        case RECV_LEAVE_MATCH:
            return recv_leave_match();
        case RECV_CREATE_GAME:
            return recv_create_game();
        case RECV_JOIN_MATCH:
            return recv_join_match();
        default:
            return std::make_shared<InvalidMessage>();
    }
}

void ServerProtocol::send_close_connection() {
    uint16_t header = htons(CLOSE_CONNECTION);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ServerProtocol::send_game_state() {
    uint16_t header = htons(SEND_GAME_STATE);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ServerProtocol::send_finish_match() {
    uint16_t header = htons(SEND_FINISH_MATCH);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}

void ServerProtocol::send_active_games(uint8_t length, std::vector<Match>& matches) {
    uint16_t header = htons(SEND_ACTIVE_GAMES);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;


    skt.sendall(&length, sizeof(length), &was_closed);
    if (was_closed)
        return;

    for (auto& match: matches) {
        skt.sendall(match.name.data(), match.name.length(), &was_closed);
        if (was_closed)
            return;
        skt.sendall(&(match.players), sizeof(match.players), &was_closed);
        if (was_closed)
            return;
    }
}

void ServerProtocol::send_game_created() {
    uint16_t header = htons(SEND_GAME_CREATED);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;
}


bool ServerProtocol::is_closed() const { return was_closed; }
