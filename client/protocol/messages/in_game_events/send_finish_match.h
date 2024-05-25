#include <cstdint>

#include "../client_message.h"

class SendFinishMatchMessage: public Message {
private:
    uint16_t id_match;

public:
    explicit SendFinishMatchMessage(uint16_t id_match);
    void run() override;
    ~SendFinishMatchMessage();
};
