#include "./common_protocol.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>
#include <endian.h>

#include "../common_liberror.h"
#include "messages/connection_events/close_connection.h"

CommonProtocol::CommonProtocol(Socket&& skt): skt(std::move(skt)), was_closed(false) {}

CommonProtocol::CommonProtocol(const std::string& hostname, const std::string& servname):
        skt(hostname.c_str(), servname.c_str()), was_closed(false) {}

uint16_t CommonProtocol::recv_two_bytes() {
    uint16_t two_bytes;

    skt.recvall(&two_bytes, sizeof(two_bytes), &was_closed);

    return ntohs(two_bytes);
}

void CommonProtocol::send_header(const uint16_t header) {
    const uint16_t header_to_n = htons(header);
    skt.sendall(&header_to_n, sizeof(header_to_n), &was_closed);
}

void CommonProtocol::send_close_connection(const uint16_t header, CloseConnectionDTO& dto) {
    send_header(header);
    dto.id_client = htons(dto.id_client);
    skt.sendall(&dto, sizeof(dto), &was_closed);
}

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
    game_state.seconds = htons(game_state.seconds);
    for (int i = 0; i < game_state.num_players; i++) {
        game_state.players[i].id = htons(game_state.players[i].id);
        game_state.players[i].health = htons(game_state.players[i].health);
        game_state.players[i].points = htons(game_state.players[i].points);
        game_state.players[i].x_pos = htons(game_state.players[i].x_pos);
        game_state.players[i].y_pos = htons(game_state.players[i].y_pos);
        for (int j = 0; j < NUM_OF_WEAPONS; j++) {
            game_state.players[i].weapons[j].ammo = htons(game_state.players[i].weapons[j].ammo);
        }
    }
    for (int i = 0; i < game_state.num_enemies; i++) {
        game_state.enemies[i].id = htons(game_state.enemies[i].id);
        game_state.enemies[i].x_pos = htons(game_state.enemies[i].x_pos);
        game_state.enemies[i].y_pos = htons(game_state.enemies[i].y_pos);
    }
    for (int i = 0; i < game_state.num_bullets; i++) {
        game_state.bullets[i].id = htobe64(game_state.bullets[i].id);
        game_state.bullets[i].x_pos = htons(game_state.bullets[i].x_pos);
        game_state.bullets[i].y_pos = htons(game_state.bullets[i].y_pos);
    }

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Game State Info:" << std::endl;
    std::cout << "Number of players: " << static_cast<int>(game_state.num_players) << std::endl;
    std::cout << "Number of enemies: " << static_cast<int>(game_state.num_enemies) << std::endl;
    std::cout << "Number of bullets: " << static_cast<int>(game_state.num_bullets) << std::endl;
    std::cout << "Game time (seconds): " << game_state.seconds << std::endl;

    for (uint8_t i = 0; i < game_state.num_players; i++) {
        std::cout << "Player " << static_cast<int>(i) << ": ID " << game_state.players[i].id
                  << ", Character " << static_cast<int>(game_state.players[i].character)
                  << ", State " << static_cast<int>(game_state.players[i].state) << ", Position ("
                  << game_state.players[i].x_pos << ", " << game_state.players[i].y_pos << ")"
                  << std::endl;
    }
    for (uint8_t i = 0; i < game_state.num_enemies; i++) {
        std::cout << "Enemy " << static_cast<int>(i) << ": Type "
                  << static_cast<int>(game_state.enemies[i].character) << ", State "
                  << static_cast<int>(game_state.enemies[i].state) << ", Position ("
                  << game_state.enemies[i].x_pos << ", " << game_state.enemies[i].y_pos << ")"
                  << std::endl;
    }

    for (uint8_t i = 0; i < game_state.num_bullets; i++) {
        std::cout << "Bullet " << static_cast<int>(i) << ": Type ID "
                  << static_cast<int>(game_state.bullets[i].bullet_type) << ", Position ("
                  << game_state.bullets[i].x_pos << ", " << game_state.bullets[i].y_pos << ")"
                  << ", Direction (" << static_cast<int>(game_state.bullets[i].direction) << ")"
                  << std::endl;
    }

    skt.sendall(&game_state, sizeof(game_state), &was_closed);
}

void CommonProtocol::send_finish_match(const uint16_t header) {
    std::cout << "sending finish match" << std::endl;
    send_header(header);
}

void CommonProtocol::send_request_active_games(const uint16_t header,
                                               RequestActiveGamesDTO& active_games) {
    send_header(header);
    active_games.id_client = htons(active_games.id_client);
    skt.sendall(&active_games, sizeof(active_games), &was_closed);
}

void CommonProtocol::send_game_created(const uint16_t header,
                                       ClientHasConnectedToMatchDTO& game_created) {
    send_header(header);
    skt.sendall(&game_created, sizeof(game_created), &was_closed);
}

void CommonProtocol::send_add_player(const uint16_t header, AddPlayerDTO dto) {
    send_header(header);
    dto.id_client = htons(dto.id_client);
    skt.sendall(&dto, sizeof(dto), &was_closed);
}

void CommonProtocol::send_game_joined(const uint16_t header,
                                      ClientHasConnectedToMatchDTO& game_joined) {
    send_header(header);
    skt.sendall(&game_joined, sizeof(game_joined), &was_closed);
}

void CommonProtocol::send_active_games(const uint16_t header, MatchInfoDTO& active_games) {
    send_header(header);
    skt.sendall(&active_games, sizeof(active_games), &was_closed);
}

void CommonProtocol::send_message(const std::shared_ptr<Message>& message) {
    message->send_message(*this);
}

void CommonProtocol::force_shutdown() {
    if (!was_closed) {
        was_closed = true;
        try {
            skt.shutdown(SHUT_RDWR);
        } catch (const std::exception& e) {
            std::cerr << "Socket shutdown failed: " << e.what() << std::endl;
        }
        skt.close();
    }
}

std::shared_ptr<Message> CommonProtocol::recv_closed_connection() {
    CloseConnectionDTO dto = {};
    skt.recvall(&dto, sizeof(dto), &was_closed);
    dto.id_client = ntohs(dto.id_client);
    return std::make_shared<CloseConnectionMessage>(dto);
}

CommonProtocol::~CommonProtocol() = default;
