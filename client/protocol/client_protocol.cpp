#include "./client_protocol.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        server(hostname.c_str(), servname.c_str()) {}

ClientProtocol::~ClientProtocol() {}
