#include "./send_finish_match.h"

SendFinishMatchMessage::SendFinishMatchMessage(uint16_t id_match) { this->id_match = id_match; }

void SendFinishMatchMessage::run() {}

SendFinishMatchMessage::~SendFinishMatchMessage() {}
