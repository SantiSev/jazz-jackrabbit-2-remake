#include "./server_receiver.h"

ServerReceiver::ServerReceiver(Socket&& skt): server_protocol(std::move(skt)) {}

ServerReceiver::~ServerReceiver() {}
