#include "message.h"

#include "snapshot.h"
#define SNAPSHOT_ID 10

MessageTest::MessageTest(size_t id): id(id) {}

void MessageTest::run() {}

size_t MessageTest::get_id() const { return id; }

// Message::Message(const Snapshot& snapshot): id(SNAPSHOT_ID) { snapshot.to_dto(); }
