#include "./server_sender.h"

ServerSender::ServerSender(Socket&& skt): server_protocol(std::move(skt)) {}

ServerSender::~ServerSender() {}
