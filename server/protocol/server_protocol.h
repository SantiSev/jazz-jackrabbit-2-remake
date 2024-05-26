#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../common/common_socket.h"
#include "./messages/connection_events/close_connection.h"
#include "./messages/in_game_events/recv_cheat_command.h"
#include "./messages/in_game_events/recv_command.h"
#include "./messages/in_game_events/recv_leave_match.h"
#include "./messages/invalid_message.h"
#include "./messages/menu_events/recv_create_game.h"
#include "./messages/menu_events/recv_join_match.h"

struct Match {
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t player;
};

class ServerProtocol {
private:
    Socket client;
    bool was_closed;

    const uint8_t recv_one_byte();
    const uint16_t recv_two_bytes();
    const std::string recv_string();

    std::unique_ptr<RecvCommandMessage> recv_command();
    std::unique_ptr<RecvCheatCommandMessage> recv_cheat_command();
    std::unique_ptr<RecvLeaveMatchMessage> recv_unjoin_match();

    std::unique_ptr<RecvCreateGameMessage> recv_create_game();
    std::unique_ptr<RecvJoinMatchMessage> recv_join_match();

public:
    explicit ServerProtocol(Socket&& skt);

    std::unique_ptr<Message> recv_message();

    void send_close_connection();

    void send_game_state();

    void send_finish_match(uint16_t id_match);

    void send_active_games(uint8_t length, std::vector<Match>& matches);

    void send_game_created();

    bool is_closed() const;
};
