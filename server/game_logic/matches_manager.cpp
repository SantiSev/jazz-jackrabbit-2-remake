#include "matches_manager.h"

#include <memory>
#include <utility>
#include <vector>

#include "../../common/common_socket.h"
#include "../protocol/server_thread_manager.h"

MatchesManager::MatchesManager():
        online(true),
        matches_number(0),
        waiting_server_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()) {}

void MatchesManager::run() {
    try {
        while (online) {
            std::shared_ptr<Message> client_message = nullptr;
            check_matches_status();

            while (waiting_server_queue->try_pop(client_message)) {
                if (client_message != nullptr) {
                    client_message->run();
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        stop_all_matches();
        clear_all_waiting_clients();
        waiting_server_queue->close();
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in matches manager: " << err.what() << "\n";
            stop();
        }
    }
}

void MatchesManager::create_new_match(ServerThreadManager* client,
                                      const std::shared_ptr<Message>& message) {
    matches_number++;
    // todo deberia ser así:
    //     std::shared_ptr<NuevaPartida> nueva_partida =
    //     std::dynamic_pointer_cast<NuevaPartida>(message);
    //     auto match = std::make_shared<Match>(nueva_partida->get_map_name(),
    //     nueva_partida->get_name(),nueva_partida->get_required_players());
    //    matches.insert({matches_number, match});
    //    match->start();
    //    Player player(0, nueva_partida->get_name(), nueva_partida->get_character_name());
    //    match->add_client_to_match(client);
    //    match->add_player_to_game(player);
    //
    // reemplazar
    auto match = std::make_shared<Match>("map 1", "my first match", REQUIRED_PLAYERS_TO_START);
    //
    matches.insert({matches_number, match});
    match->start();
    match->add_client_to_match(client, "pepe", "mago");
    //
}

void MatchesManager::join_match(TestClientServer* client, const std::shared_ptr<Message>& message) {
    //    auto join_match = std::dynamic_pointer_cast<JoinMatch>(message);
    //    auto it = matches.find(join_match->get_id());
    //    if (it != matches.end()) {
    //        it->second->add_client_to_match(client);
    //        Player player(0, join_match->get_name(), join_match->get_character_name());
    //        it->second->add_player_to_game(player);
    //    }
}

void MatchesManager::check_matches_status() {
    for (auto it = matches.begin(); it != matches.end();) {
        if (it->second->has_match_ended()) {
            std::cout << "Match " << it->first << " " << it->second->get_match_name()
                      << " has ended.\n";
            stop_finished_match(it->second.get());
            matches.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

void MatchesManager::stop_finished_match(Match* match) {
    match->stop();
    match->join();
    std::vector<size_t> ids = match->get_clients_ids();
    for (auto id: ids) {
        auto it = clients.begin();
        while (it != clients.end()) {
            if ((*it)->get_client_id() == id) {
                (*it)->stop();
                delete (*it);
                clients.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }
}

void MatchesManager::stop_all_matches() {
    for (auto& match: matches) {
        match.second->stop();
        match.second->join();
    }
    matches.clear();
}

std::vector<matchesDTO> MatchesManager::return_matches_lists() {
    std::vector<matchesDTO> matches_list;
    for (auto& match: matches) {
        matchesDTO matchDTO;
        matchDTO.match_name = match.second->get_match_name();
        matchDTO.match_id = match.first;
        matchDTO.minutes = match.second->get_minutes();
        matchDTO.seconds = match.second->get_seconds();
        matchDTO.num_actual_players = match.second->get_num_players();
        matchDTO.max_players = match.second->get_max_players();
        matches_list.push_back(matchDTO);
    }
    return matches_list;
}

void MatchesManager::add_player_to_game(Player& player, size_t match_id) {
    //    auto it = matches.find(match_id);
    //    if (it != matches.end()) {
    //        it->second->add_player_to_game(player, std::string());
    //    }
}

void MatchesManager::add_new_client(Socket client_socket) {
    clients_connected++;
    auto sender_queue = std::make_shared<Queue<std::shared_ptr<Message>>>();
    auto client =
            new ServerThreadManager(std::move(client_socket), waiting_server_queue, sender_queue);
    //    auto message =std::make_shared<ConnectedMessage>(clients_connected);  // le mando su id
    //    para que lo guarde client->get_sender_queue()->push(message);
    client->set_client_id(clients_connected);
    clients.push_back(client);
    create_new_match(clients.front(), nullptr);  // esto normalmente no se llama aca, quitar cuando
                                                 // se conecte mediante mensajes.
                                                 // ATENCION FALLA SI CONECTAN MAS DE UNO PORQUE SE
                                                 // USA EL FRONT(). ES PARA TESTEAR
}

void MatchesManager::clear_all_waiting_clients() {
    for (auto& client: clients) {
        client->stop();
        delete client;
    }
    clients.clear();
}

void MatchesManager::send_match_lists(TestClientServer* client) {
    // todo deberia ser así
    // client->get_sender_queue()->push(return_matches_lists());
}

void MatchesManager::stop() { online = false; }
