#include <memory>
#include <string>

#include "../../common/common_socket.h"
#include "../../common/protocol/messages/connection_events/close_connection.h"
#include "../../common/protocol/messages/in_game_events/send_finish_match.h"
#include "../../common/protocol/messages/in_game_events/send_game_state.h"
#include "../../common/protocol/messages/invalid_message.h"
#include "../../common/protocol/messages/menu_events/send_active_games.h"
#include "../../common/protocol/messages/menu_events/send_game_created.h"

class ClientProtocol {
private:
    Socket server;
    bool was_closed;

    const uint8_t recv_one_byte();  // unusedPrivateFunction
    const uint16_t recv_two_bytes();
    const std::string recv_string();  // unusedPrivateFunction

    std::unique_ptr<SendFinishMatchMessage> recv_finish_match();
    std::unique_ptr<SendGameStateMessage> recv_game_state();

    std::unique_ptr<SendActiveGamesMessage> recv_active_games();
    std::unique_ptr<SendGameCreatedMessage> recv_game_created();

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    std::unique_ptr<Message> recv_message();

    void send_command(uint16_t id_player, uint8_t id_command);

    void send_cheat_command(uint16_t id_player, uint8_t id_cheat_command);

    void send_leave_match(uint16_t id_player);

    void send_create_game(uint16_t id_player, std::string& match_name);

    void send_join_match(uint16_t id_player, uint16_t id_match, uint8_t player_character);

    ~ClientProtocol();
};
