#include "message.h"

Message::Message(size_t id): id(id) {}

void Message::run() {}

size_t Message::get_id() const { return id; }
