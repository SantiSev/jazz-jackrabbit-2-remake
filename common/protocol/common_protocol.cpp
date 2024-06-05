#include "./common_protocol.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>

CommonProtocol::CommonProtocol(Socket&& skt): skt(std::move(skt)), was_closed(false) {}

CommonProtocol::CommonProtocol(const std::string& hostname, const std::string& servname):
        skt(hostname.c_str(), servname.c_str()), was_closed(false) {}

const uint16_t CommonProtocol::recv_two_bytes() {
    uint16_t two_bytes;

    skt.recvall(&two_bytes, sizeof(two_bytes), &was_closed);

    return ntohs(two_bytes);
}

void CommonProtocol::send_header(const uint16_t header) {
    const uint16_t header_to_n = htons(header);
    skt.sendall(&header_to_n, sizeof(header_to_n), &was_closed);
}

void CommonProtocol::send_close_connection(const uint16_t header) { send_header(header); }

void CommonProtocol::send_acpt_connection(const uint16_t header, const id_client_t id_client) {
    send_header(header);
    id_client_t id_client_to_n = htons(id_client);
    skt.sendall(&id_client_to_n, sizeof(id_client_to_n), &was_closed);
}

void CommonProtocol::send_cheat_command(const uint16_t header, CheatCommandDTO& cheat_command) {
    send_header(header);
    cheat_command.id_player = htons(cheat_command.id_player);
    skt.sendall(&cheat_command, sizeof(cheat_command), &was_closed);
}

void CommonProtocol::send_command(const uint16_t header, CommandDTO& command) {
    send_header(header);
    command.id_player = htons(command.id_player);
    skt.sendall(&command, sizeof(command), &was_closed);
}

void CommonProtocol::send_leave_match(const uint16_t header, LeaveMatchDTO& leave_match) {
    send_header(header);
    leave_match.id_player = htons(leave_match.id_player);
    skt.sendall(&leave_match, sizeof(leave_match), &was_closed);
}

void CommonProtocol::send_create_game(const uint16_t header, CreateGameDTO& create_game) {
    send_header(header);
    create_game.id_client = htons(create_game.id_client);
    skt.sendall(&create_game, sizeof(create_game), &was_closed);
}

void CommonProtocol::send_join_match(const uint16_t header, JoinMatchDTO& join_match) {
    send_header(header);
    join_match.id_client = htons(join_match.id_client);
    join_match.id_match = htons(join_match.id_match);
    skt.sendall(&join_match, sizeof(join_match), &was_closed);
}

void CommonProtocol::send_game_state(const uint16_t header, GameStateDTO& game_state) {
    send_header(header);
    skt.sendall(&game_state, sizeof(game_state), &was_closed);
}

void CommonProtocol::send_finish_match(const uint16_t header, FinishMatchDTO& finish_match) {
    send_header(header);
    skt.sendall(&finish_match, sizeof(finish_match), &was_closed);
}

void CommonProtocol::send_request_active_games(const uint16_t header,
                                               RequestActiveGamesDTO& active_games) {
    send_header(header);
    skt.sendall(&active_games, sizeof(active_games), &was_closed);
}

void CommonProtocol::send_game_created(const uint16_t header, GameCreatedDTO& game_created) {
    send_header(header);
    skt.sendall(&game_created, sizeof(game_created), &was_closed);
}

void CommonProtocol::send_game_joined(const uint16_t header, ClientJoinedMatchDTO& game_joined) {
    send_header(header);
    skt.sendall(&game_joined, sizeof(game_joined), &was_closed);
}

void CommonProtocol::send_active_games(const uint16_t header, MatchInfoDTO& active_games) {
    send_header(header);
    skt.sendall(&active_games, sizeof(active_games), &was_closed);
}

void CommonProtocol::send_message(std::shared_ptr<Message> message) {
    message->send_message(*this);
}

void CommonProtocol::force_shutdown() {
    was_closed = true;
    skt.shutdown(2);
    skt.close();
}

CommonProtocol::~CommonProtocol() = default;
