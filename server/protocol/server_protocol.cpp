#include "./server_protocol.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>

#include "../../common/common_liberror.h"

ServerProtocol::ServerProtocol(Socket&& skt): CommonProtocol(std::move(skt)) {}

std::shared_ptr<RecvCommandMessage> ServerProtocol::recv_command() {
    CommandDTO command = {};
    skt.recvall(&command, sizeof(command), &was_closed);
    command.id_player = ntohs(command.id_player);
    return std::make_shared<RecvCommandMessage>(command);
}

std::shared_ptr<RecvCheatCommandMessage> ServerProtocol::recv_cheat_command() {
    CheatCommandDTO cheat_command = {};
    skt.recvall(&cheat_command, sizeof(cheat_command), &was_closed);
    cheat_command.id_player = ntohs(cheat_command.id_player);
    return std::make_shared<RecvCheatCommandMessage>(cheat_command);
}

std::shared_ptr<RecvLeaveMatchMessage> ServerProtocol::recv_leave_match() {
    LeaveMatchDTO leave_match = {};
    skt.recvall(&leave_match, sizeof(leave_match), &was_closed);
    leave_match.id_player = ntohs(leave_match.id_player);
    return std::make_shared<RecvLeaveMatchMessage>(leave_match);
}

std::shared_ptr<RecvCreateGameMessage> ServerProtocol::recv_create_game() {
    CreateGameDTO create_game = {};
    skt.recvall(&create_game, sizeof(create_game), &was_closed);
    create_game.id_client = ntohs(create_game.id_client);
    return std::make_shared<RecvCreateGameMessage>(create_game);
}

std::shared_ptr<Message> ServerProtocol::recv_req_active_games() {
    RequestActiveGamesDTO active_games = {};
    skt.recvall(&active_games, sizeof(active_games), &was_closed);
    active_games.id_client = ntohs(active_games.id_client);
    return std::make_shared<SendRequestGamesMessage>(active_games);
}

std::shared_ptr<Message> ServerProtocol::recv_add_player() {
    AddPlayerDTO dto = {};
    skt.recvall(&dto, sizeof(dto), &was_closed);
    dto.id_client = ntohs(dto.id_client);
    return std::make_shared<AddPlayerMessage>(dto);
}

std::shared_ptr<RecvJoinMatchMessage> ServerProtocol::recv_join_match() {
    JoinMatchDTO join_match = {};
    skt.recvall(&join_match, sizeof(join_match), &was_closed);
    join_match.id_client = ntohs(join_match.id_client);
    join_match.id_match = ntohs(join_match.id_match);
    return std::make_shared<RecvJoinMatchMessage>(join_match);
}

std::shared_ptr<Message> ServerProtocol::recv_message() {
    try {
        const uint16_t header = recv_two_bytes();
        printf("El valor de header es: %u\n", header);

        switch (header) {
            case CLOSE_CONNECTION:
                return recv_closed_connection();
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
            case RECV_REQUEST_ACTIVE_GAMES:
                return recv_req_active_games();
            case ADD_PLAYER:
                return recv_add_player();
            default:
                return std::make_shared<InvalidMessage>();
        }
    } catch (const LibError& e) {
        force_shutdown();
    }
    return std::make_shared<InvalidMessage>();
}

bool ServerProtocol::is_closed() const { return was_closed; }
