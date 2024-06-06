#ifndef _CLIENT_PROTOCOL_H
#define _CLIENT_PROTOCOL_H

#include <memory>
#include <string>
#include <vector>

#include "../../common/protocol/common_protocol.h"
#include "../../common/protocol/messages/connection_events/acpt_connection.h"
#include "../../common/protocol/messages/connection_events/close_connection.h"
#include "../../common/protocol/messages/in_game_events/recv_cheat_command.h"
#include "../../common/protocol/messages/in_game_events/recv_command.h"
#include "../../common/protocol/messages/in_game_events/recv_leave_match.h"
#include "../../common/protocol/messages/in_game_events/send_finish_match.h"
#include "../../common/protocol/messages/in_game_events/send_game_state.h"
#include "../../common/protocol/messages/invalid_message.h"
#include "../../common/protocol/messages/menu_events/recv_create_game.h"
#include "../../common/protocol/messages/menu_events/recv_join_match.h"
#include "../../common/protocol/messages/menu_events/send_game_created.h"
#include "../../common/protocol/messages/menu_events/send_game_joined.h"
#include "../../common/protocol/messages/menu_events/send_request_games.h"

class ClientProtocol: public CommonProtocol {
private:
    std::shared_ptr<SendFinishMatchMessage> recv_finish_match();
    std::shared_ptr<SendGameStateMessage> recv_game_state();
    std::shared_ptr<AcptConnection> recv_acpt_connection();
    std::shared_ptr<SendRequestGamesMessage> recv_active_games();
    std::shared_ptr<SendGameCreatedMessage> recv_game_created();

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    std::shared_ptr<Message> recv_message();

    ~ClientProtocol();

    std::shared_ptr<Message> recv_game_joined();
};

#endif
