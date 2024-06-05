#ifndef _COMMON_PROTOCOL_H
#define _COMMON_PROTOCOL_H
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../common_socket.h"
#include "./common_dto.h"
#include "./messages/common_message.h"

class Message;

class CommonProtocol {
protected:
    Socket skt;
    bool was_closed;

    const uint16_t recv_two_bytes();
    void send_header(const uint16_t header);

public:
    explicit CommonProtocol(Socket&& skt);
    CommonProtocol(const std::string& hostname, const std::string& servname);
    void send_close_connection(const uint16_t header);
    void send_acpt_connection(const uint16_t header, const id_client_t id_client);
    void send_cheat_command(const uint16_t header, CheatCommandDTO& cheat_command);
    void send_command(const uint16_t header, CommandDTO& command);
    void send_leave_match(const uint16_t header, LeaveMatchDTO& leave_match);
    void send_finish_match(const uint16_t header, FinishMatchDTO& finish_match);
    void send_game_state(const uint16_t header, GameStateDTO& game_state);
    void send_create_game(const uint16_t header, CreateGameDTO& create_game);
    void send_join_match(const uint16_t header, JoinMatchDTO& join_match);
    void send_request_active_games(const uint16_t header, RequestActiveGamesDTO& active_games);
    void send_game_created(const uint16_t header, ClientHasConnectedToMatchDTO& game_created);
    void send_message(std::shared_ptr<Message> message);
    void force_shutdown();
    ~CommonProtocol();

    void send_game_joined(const uint16_t header, ClientHasConnectedToMatchDTO& game_joined);

    void send_active_games(const uint16_t header, MatchInfoDTO& active_games);
};

#endif
