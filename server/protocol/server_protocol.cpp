#include "./server_protocol.h"

#include <vector>

#include <arpa/inet.h>

#include "../../common/protocol/messages/connection_events/close_connection.h"
#include "../../common/protocol/messages/invalid_message.h"

ServerProtocol::ServerProtocol(Socket&& skt): CommonProtocol(std::move(skt)) {}

std::shared_ptr<RecvCommandMessage> ServerProtocol::recv_command() {
    CommandDTO command = {};
    skt.sendall(&command, sizeof(command), &was_closed);
    command.id_player = ntohs(command.id_player);
    return std::make_shared<RecvCommandMessage>(command);
}

std::shared_ptr<RecvCheatCommandMessage> ServerProtocol::recv_cheat_command() {
    CheatCommandDTO cheat_command = {};
    skt.sendall(&cheat_command, sizeof(cheat_command), &was_closed);
    cheat_command.id_player = ntohs(cheat_command.id_player);
    return std::make_shared<RecvCheatCommandMessage>(cheat_command);
}

std::shared_ptr<RecvLeaveMatchMessage> ServerProtocol::recv_leave_match() {
    LeaveMatchDTO leave_match = {};
    skt.sendall(&leave_match, sizeof(leave_match), &was_closed);
    leave_match.id_player = ntohs(leave_match.id_player);
    return std::make_shared<RecvLeaveMatchMessage>(leave_match);
}

std::shared_ptr<RecvCreateGameMessage> ServerProtocol::recv_create_game() {
    CreateGameDTO create_game = {};
    skt.sendall(&create_game, sizeof(create_game), &was_closed);
    create_game.id_client = ntohs(create_game.id_client);
    return std::make_shared<RecvCreateGameMessage>(create_game);
}

std::shared_ptr<RecvJoinMatchMessage> ServerProtocol::recv_join_match() {
    JoinMatchDTO join_match = {};
    skt.sendall(&join_match, sizeof(join_match), &was_closed);
    join_match.id_client = ntohs(join_match.id_client);
    join_match.id_match = ntohs(join_match.id_match);
    return std::make_shared<RecvJoinMatchMessage>(join_match);
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

bool ServerProtocol::is_closed() const { return was_closed; }
