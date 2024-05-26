#include <cstdint>
#include <string>
#include <vector>

#include "../client_message.h"

struct Match {
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t player;
};

class SendActiveGamesMessage: public Message {
private:
    std::vector<Match> matches;

public:
    explicit SendActiveGamesMessage(std::vector<Match>&& matches);
    void run() override;
    ~SendActiveGamesMessage();
};
