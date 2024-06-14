#ifndef TP_FINAL_ADD_PLAYER_H
#define TP_FINAL_ADD_PLAYER_H

#include "../common_message.h"

class AddPlayerMessage: public Message {

public:
    AddPlayerDTO dto;

    explicit AddPlayerMessage(const AddPlayerDTO& dto);

    void run(MessageHandler& handler) override;

    void send_message(CommonProtocol& protocol) override;

    ~AddPlayerMessage() override;
};

#endif
