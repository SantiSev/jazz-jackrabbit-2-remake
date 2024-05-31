#include <vector>

#include "../../../message/snapshot.h"
#include "../common_message.h"

class SendGameStateMessage: public Message {
private:
    int match_seconds = 0;
    int match_minutes = 0;
    std::vector<Player> players;
    std::vector<Enemies> enemies;

public:
    SendGameStateMessage();
    explicit SendGameStateMessage(const Snapshot& snapshot);

    void run() override;
    ~SendGameStateMessage() override;
};
