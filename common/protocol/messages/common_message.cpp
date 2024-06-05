#include "./common_message.h"

Message::Message(const uint16_t header): header(header) {}

uint16_t Message::get_header() const { return header; }

void Message::run(MessageHandler& handler) {}


Message::~Message() = default;
