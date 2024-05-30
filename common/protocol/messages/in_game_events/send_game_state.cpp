#include "./send_game_state.h"

SendGameStateMessage::SendGameStateMessage() {}

void SendGameStateMessage::send_message(CommonProtocol& protocol) { protocol.send_game_state(); }

void SendGameStateMessage::run() {}

SendGameStateMessage::~SendGameStateMessage() {}
