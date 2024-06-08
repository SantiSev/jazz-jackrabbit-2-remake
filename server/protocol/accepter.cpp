#include "accepter.h"

#include <algorithm>

#include "../../common/common_socket.h"
#include "../game_logic/matches_manager.h"


ServerAccepter::ServerAccepter(const std::string& port): skt(Socket(port.c_str())) {}

void ServerAccepter::run() {
    try {
        matches_manager.start();
        while (_keep_running) {
            Socket peer = skt.accept();
            if (!_keep_running) {
                break;
            }
            matches_manager.add_new_client_to_manager(std::move(peer));
        }
    } catch (const std::exception& err) {
        if (_keep_running) {
            std::cerr << "An exception was caught in accepter: " << err.what() << "\n";
        }
    }
}

void ServerAccepter::stop() {
    _keep_running = false;
    skt.shutdown(SHUT_RDWR);  // TODO revisar esto
    skt.close();
    matches_manager.stop();
    matches_manager.join();
}
