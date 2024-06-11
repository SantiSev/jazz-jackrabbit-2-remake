#ifndef _SERVER_PROTOCOL_H
#define _SERVER_PROTOCOL_H

#include <memory>
#include <string>
#include <vector>

#include "../../common/protocol/common_protocol.h"
#include "../../common/protocol/messages/connection_events/close_connection.h"
#include "../../common/protocol/messages/in_game_events/add_player.h"
#include "../../common/protocol/messages/in_game_events/recv_cheat_command.h"
#include "../../common/protocol/messages/in_game_events/recv_command.h"
#include "../../common/protocol/messages/in_game_events/recv_leave_match.h"
#include "../../common/protocol/messages/in_game_events/send_finish_match.h"
#include "../../common/protocol/messages/in_game_events/send_game_state.h"
#include "../../common/protocol/messages/invalid_message.h"
#include "../../common/protocol/messages/menu_events/recv_active_games.h"
#include "../../common/protocol/messages/menu_events/recv_create_game.h"
#include "../../common/protocol/messages/menu_events/recv_join_match.h"
#include "../../common/protocol/messages/menu_events/send_connected_to_game.h"
#include "../../common/protocol/messages/menu_events/send_request_games.h"

class ServerProtocol: public CommonProtocol {
private:
    std::shared_ptr<RecvCommandMessage> recv_command();
    std::shared_ptr<RecvCheatCommandMessage> recv_cheat_command();
    std::shared_ptr<RecvLeaveMatchMessage> recv_leave_match();

    std::shared_ptr<RecvCreateGameMessage> recv_create_game();
    std::shared_ptr<RecvJoinMatchMessage> recv_join_match();

public:
    explicit ServerProtocol(Socket&& skt);

    std::shared_ptr<Message> recv_message();

    bool is_closed() const;

    std::shared_ptr<Message> recv_req_active_games();

    std::shared_ptr<Message> recv_add_player();
};

#endif
