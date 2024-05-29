#include "message.h"

#include "snapshot.h"
#define SNAPSHOT_ID 10

Message::Message(size_t id): id(id) {}

void Message::run() {}

size_t Message::get_id() const { return id; }

Message::Message(const Snapshot& snapshot): id(SNAPSHOT_ID) { snapshot.to_dto(); }
