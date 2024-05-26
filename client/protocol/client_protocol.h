#include <memory>
#include <string>

#include "../../common/common_socket.h"
#include "./messages/connection_events/close_connection.h"
#include "./messages/in_game_events/send_finish_match.h"
#include "./messages/in_game_events/send_game_state.h"
#include "./messages/invalid_message.h"
#include "./messages/menu_events/send_active_games.h"
#include "./messages/menu_events/send_game_created.h"

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

    ~ClientProtocol();
};
