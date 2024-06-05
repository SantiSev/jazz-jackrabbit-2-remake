#include "./client_thread_manager.h"

ClientThreadManager::ClientThreadManager(const std::string& hostname, const std::string& servname,
                                         Queue<std::shared_ptr<Message>>& receiver_queue,
                                         Queue<std::shared_ptr<Message>>& sender_queue):
        client_protocol(hostname, servname),
        receiver(client_protocol, receiver_queue),
        sender(client_protocol, sender_queue) {
    receiver.start();
    sender.start();
}

ClientProtocol& ClientThreadManager::get_protocol() { return client_protocol; }

ClientThreadManager::~ClientThreadManager() {
    receiver.join();
    receiver.kill();
    sender.join();
    sender.kill();
}

void ClientThreadManager::set_active_games(MatchInfoDTO dto) {
    std::cout << "primera partida-> mapa:" << dto.active_games[0].map
              << " max players:" << dto.active_games[0].players_max
              << " players_ingame:" << dto.active_games[0].players_ingame << std::endl;
}
