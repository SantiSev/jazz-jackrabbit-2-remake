#include "matches_manager.h"

#include <memory>
#include <utility>
#include <vector>

MatchesManager::MatchesManager():
        online(true),
        matches_number(0),
        waiting_server_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()),
        message_handler(*this) {}

void MatchesManager::run() {
    try {
        std::shared_ptr<Message> client_message;
        while (online) {
            client_message = nullptr;
            check_matches_status();

            while (waiting_server_queue->try_pop(client_message)) {
                if (client_message != nullptr) {
                    client_message->run(message_handler);
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

void MatchesManager::create_new_match(const CreateGameDTO& dto) {
    matches_number++;
    auto match = std::make_shared<Match>(dto.map_name, dto.max_players);
    matches.insert({matches_number, match});
    match->start();
    match->add_client_to_match(get_client_by_id(dto.id_client), "jugador 1",
                               dto.character_selected);
    send_id_player_to_client(dto);
}

void MatchesManager::send_id_player_to_client(const CreateGameDTO& dto) {
    ClientHasConnectedToMatchDTO game_created = {1};
    auto send_game_created = std::make_shared<SendConnectedToGameMessage>(game_created);
    get_client_by_id(dto.id_client)
            ->get_sender_queue()
            ->push(send_game_created);  // todo ver si funciona así
}

ServerThreadManager* MatchesManager::get_client_by_id(size_t id) {
    auto it = std::find_if(clients.begin(), clients.end(), [id](ServerThreadManager* client) {
        return client->get_client_id() == id;
    });

    return (it != clients.end()) ? *it : nullptr;
}


void MatchesManager::join_match(const JoinMatchDTO& dto) {
    auto it = matches.find(dto.id_match);
    if (it != matches.end()) {
        it->second->add_client_to_match(get_client_by_id(dto.id_match), "pepo_joineado",
                                        dto.player_character);
        send_joined_info_to_client(
                dto,
                it->second->get_num_players());  // todo ver si funciona y si el numero está bien
    }
}

void MatchesManager::send_joined_info_to_client(const JoinMatchDTO& dto,
                                                const uint16_t& player_number) {
    uint16_t num_players = player_number;
    num_players++;
    ClientHasConnectedToMatchDTO joined_dto = {num_players};
    auto joined_message = std::make_shared<SendConnectedToGameMessage>(joined_dto);
    get_client_by_id(dto.id_match)->get_sender_queue()->push(joined_message);
}

void MatchesManager::add_new_client_to_manager(Socket client_socket) {
    clients_connected++;
    auto client = new ServerThreadManager(std::move(client_socket), waiting_server_queue);
    auto message = std::make_shared<AcptConnection>(clients_connected);  // le mando su id
    client->get_sender_queue()->push(message);
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

MatchInfoDTO MatchesManager::return_matches_lists() {
    MatchInfoDTO matches_lists{};
    matches_lists.num_games = matches.size();
    size_t i = 0;
    for (auto& match: matches) {
        matches_lists.active_games[i].map = match.second->get_map();
        matches_lists.active_games[i].players_ingame = match.second->get_num_players();
        matches_lists.active_games[i].players_max = match.second->get_max_players();
    }
    return matches_lists;
}

void MatchesManager::send_match_lists(RequestActiveGamesDTO dto) {
    auto matches_lists = return_matches_lists();
    auto matches_message = std::make_shared<RecvActiveGames>(matches_lists);
    get_client_by_id(dto.id_client)->get_sender_queue()->push(matches_message);
}

void MatchesManager::check_matches_status() {
    for (auto it = matches.begin(); it != matches.end();) {
        if (it->second->has_match_ended()) {
            std::cout << "Match " << it->first << " " << it->second->get_map() << " has ended.\n";
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

void MatchesManager::stop() { online = false; }
