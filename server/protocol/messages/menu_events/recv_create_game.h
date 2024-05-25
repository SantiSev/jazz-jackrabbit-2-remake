#include <string>

#include "../server_message.h"

class RecvCreateGameMessage: public Message {
private:
    uint16_t id_player;
    std::string match_name;

public:
    RecvCreateGameMessage(uint16_t id_player, const std::string& match_name);
    void run() override;
    ~RecvCreateGameMessage();
};
