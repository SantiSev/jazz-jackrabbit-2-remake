#ifndef _SERVER_PROTOCOL_H
#define _SERVER_PROTOCOL_H
#include <memory>
#include <string>
#include <vector>

//#include "../../common/protocol/common_protocol.h"
#include "../../common/protocol/messages/common_message.h"
#include "../../common/protocol/messages/in_game_events/recv_cheat_command.h"
#include "../../common/protocol/messages/in_game_events/recv_command.h"
#include "../../common/protocol/messages/in_game_events/recv_leave_match.h"
#include "../../common/protocol/messages/menu_events/recv_create_game.h"
#include "../../common/protocol/messages/menu_events/recv_join_match.h"


class ServerProtocol: public CommonProtocol {
private:
    std::shared_ptr<RecvCommandMessage> recv_command();
    std::shared_ptr<RecvCheatCommandMessage> recv_cheat_command();
    std::shared_ptr<RecvLeaveMatchMessage> recv_unjoin_match();

    std::shared_ptr<RecvCreateGameMessage> recv_create_game();
    std::shared_ptr<RecvJoinMatchMessage> recv_join_match();

public:
    explicit ServerProtocol(Socket&& skt);

    std::shared_ptr<Message> recv_message();

    void send_message(std::shared_ptr<Message> msg);

    void send_close_connection() override;

    void send_game_state() override;

    void send_finish_match() override;

    void send_active_games(uint8_t length, std::vector<MatchDTO>& matches) override;

    void send_game_created() override;

    bool is_closed() const;
};

#endif
