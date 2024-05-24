#include <map>
#include <memory>
#include <string>

#include "../../common/common_socket.h"
#include "./messages/server_message.h"

class ServerProtocol {
private:
    Socket client;
    bool was_closed;

    const uint16_t recv_header();

    const uint16_t recv_id_player();
    const uint8_t recv_id_command();
    const uint8_t recv_id_cheat_command();
    const std::string recv_match_name();
    const uint16_t recv_id_match();
    const uint8_t recv_player_character();

    std::shared_ptr<RecvCommandMessage> recv_command();
    std::shared_ptr<RecvCheatCommandMessage> recv_cheat_command();
    std::shared_ptr<RecvUnjoinMatchMessage> recv_unjoin_match();

    std::shared_ptr<RecvCreateGameMessage> recv_create_game();
    std::shared_ptr<RecvJoinMatchMessage> recv_join_match();

public:
    explicit ServerProtocol(Socket&& skt);

    std::shared_ptr<Message> recv_message();

    bool is_closed() const;
};
