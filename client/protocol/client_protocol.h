#include <string>

#include "../../common/common_socket.h"

class ClientProtocol {
private:
    Socket server;
    bool was_closed;

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    void send_command(uint16_t id_player, uint8_t id_command);

    void send_cheat_command(uint16_t id_player, uint8_t id_cheat_command);

    void send_leave_match(uint16_t id_player);

    void send_create_game(uint16_t id_player, std::string& match_name);

    void send_join_match(uint16_t id_player, uint16_t id_match, uint8_t player_charecter);

    ~ClientProtocol();
};
