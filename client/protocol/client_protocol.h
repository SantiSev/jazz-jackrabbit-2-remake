#include <string>

#include "../../common/common_socket.h"

class ClientProtocol {
private:
    Socket server;
    bool was_closed;

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    void send_command(uint16_t id_player, uint8_t id_command);

    void send_cheat_command();

    void send_leave_match();

    void send_create_game();

    void send_join_match();

    ~ClientProtocol();
};
