#include "matches_manager.h"

#include <memory>
#include <utility>
#include <vector>

#include "../../common/protocol/messages/common_message.h"

MatchesManager::MatchesManager():
        online(true),
        matches_number(0),
        waiting_server_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()) {}

void MatchesManager::run() {
    try {
        std::shared_ptr<Message> client_message;
        while (online) {
            client_message = nullptr;
            check_matches_status();

            while (waiting_server_queue->try_pop(client_message)) {
                if (client_message != nullptr) {
                    client_message->run(*this);
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

void MatchesManager::create_new_match(const uint16_t& id_client, const std::string& match_name,
                                      const size_t& max_players, const std::string& map_name,
                                      const uint8_t& character_selected) {
    matches_number++;
    auto match = std::make_shared<Match>(map_name, match_name, max_players);
    matches.insert({matches_number, match});
    match->start();
    match->add_client_to_match(get_client_by_id(id_client), "jugador 1", character_selected);
}

ServerThreadManager* MatchesManager::get_client_by_id(size_t id) {
    auto it = std::find_if(clients.begin(), clients.end(), [id](ServerThreadManager* client) {
        return client->get_client_id() == id;
    });

    return (it != clients.end()) ? *it : nullptr;
}

void MatchesManager::join_match(const id_player_t& client_id, const id_match_t& match_id,
                                const character_t& character) {
    auto it = matches.find(match_id);
    if (it != matches.end()) {
        it->second->add_client_to_match(get_client_by_id(client_id), "pepo", character);
    }
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

void MatchesManager::add_new_client(Socket client_socket) {
    clients_connected++;
    auto client = new ServerThreadManager(std::move(client_socket), waiting_server_queue);
    //    auto message =std::make_shared<ConnectedMessage>(clients_connected);  // le mando su id
    //    para que lo guarde client->get_sender_queue()->push(message);
    client->set_client_id(clients_connected);
    clients.push_back(client);
}

void MatchesManager::clear_all_waiting_clients() {
    for (auto& client: clients) {
        client->stop();
        delete client;
    }
    clients.clear();
}

void MatchesManager::send_match_lists(ServerThreadManager* client) {
    //     client->get_sender_queue()->push(return_matches_lists());
}

void MatchesManager::stop() { online = false; }
