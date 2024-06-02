#ifndef CLIENT_PROTOCOL
#define CLIENT_PROTOCOL

#include <memory>
#include <string>
#include <vector>

#include "../../common/common_socket.h"
#include "../../common/protocol/common_protocol.h"
#include "../../common/protocol/messages/connection_events/close_connection.h"
#include "../../common/protocol/messages/connection_events/made_first_connection.h"
#include "../../common/protocol/messages/in_game_events/send_finish_match.h"
#include "../../common/protocol/messages/in_game_events/send_game_state.h"
#include "../../common/protocol/messages/invalid_message.h"
#include "../../common/protocol/messages/menu_events/send_active_games.h"
#include "../../common/protocol/messages/menu_events/send_game_created.h"


class ClientProtocol: public CommonProtocol {
private:
    uint16_t my_client_id;
    uint16_t my_player_id;
    std::shared_ptr<SendFinishMatchMessage> recv_finish_match();
    std::shared_ptr<SendGameStateMessage> recv_game_state();
    std::shared_ptr<MadeFirstConnection> recv_made_connection();
    std::shared_ptr<SendActiveGamesMessage> recv_active_games();
    std::shared_ptr<SendGameCreatedMessage> recv_game_created();

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);
    std::shared_ptr<Message> recv_message();
    void send_command(uint16_t id_player, uint8_t id_command);
    void send_cheat_command(uint16_t id_player, uint8_t id_cheat_command);
    void send_leave_match(uint16_t id_player);
    void send_create_game(uint16_t client_id, std::string& match_name, uint8_t character);
    void send_join_match(uint16_t id_player, uint16_t id_match, uint8_t player_character);
    void send_close_connection() override;
    void send_game_state() override;
    void send_finish_match() override;
    void send_first_connection(uint16_t id) override;
    void send_active_games(uint8_t length, std::vector<MatchDTO>& matches) override;
    void send_game_created(uint16_t id_player) override;
    void set_my_client_id(const uint16_t& new_client_id);
    void set_my_player_id(const uint16_t& new_player_id);
    uint16_t get_client_id() const;
    uint16_t get_player_id() const;

    void send_message(const std::shared_ptr<Message>& msg);
};

#endif
