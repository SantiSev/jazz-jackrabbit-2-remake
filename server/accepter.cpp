#include "accepter.h"

#include <algorithm>

#include "../common/common_socket.h"
#include "game_logic/matches_manager.h"


ServerAccepter::ServerAccepter(const std::string& port):
        skt(Socket(port.c_str())), online(true), matches_manager() {}

void ServerAccepter::run() {

    try {
        matches_manager.start();
        while (online) {
            Socket peer = skt.accept();
            if (!online) {
                break;
            }
            matches_manager.add_new_client(std::move(peer));
        }
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in accepter: " << err.what() << "\n";
        }
    }
}

void ServerAccepter::stop() {
    online = false;
    skt.shutdown(2);
    skt.close();
    matches_manager.stop();
    matches_manager.join();
}
