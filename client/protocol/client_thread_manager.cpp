#include "./client_thread_manager.h"

ClientThreadManager::ClientThreadManager(const std::string& hostname, const std::string& servname,
                                         Queue<std::shared_ptr<Message>>& receiver_queue,
                                         Queue<std::shared_ptr<Message>>& sender_queue):
        client_protocol(hostname, servname),
        receiver(client_protocol, receiver_queue),
        sender(client_protocol, sender_queue),
        my_client_id(0),
        my_player_id(0),
        message_handler(*this) {
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

void ClientThreadManager::set_my_client_id(const id_client_t& new_client_id) {
    my_client_id = new_client_id;
}

uint16_t ClientThreadManager::get_client_id() const { return my_client_id; }

void ClientThreadManager::set_my_player_id(const id_player_t& new_player_id) {
    my_player_id = new_player_id;
}
uint16_t ClientThreadManager::get_player_id() const { return my_player_id; }

void ClientThreadManager::set_active_games(ActiveGamesDTO dto) {
    std::cout << "primera partida-> mapa:" << dto.map << " max players:" << dto.players_max
              << " players_ingame:" << dto.players_ingame << std::endl;
}
