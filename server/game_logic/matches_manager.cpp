#include "matches_manager.h"

#include <memory>
#include <utility>
#include <vector>

MatchesManager::MatchesManager():
        online(true),
        matches_number(0),
        message_handler(*this, manager_queue),
        client_monitor(),
        manager_queue(Queue<std::shared_ptr<Message>>()) {}

void MatchesManager::run() {
    try {
        while (online) {
            std::shared_ptr<Message> client_message = nullptr;
            //            check_matches_status();

            manager_queue.try_pop(client_message);
            if (client_message) {
                client_message->run(message_handler);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << "stopping matches" << std::endl;
        stop_all_matches();
        std::cout << "clearing all clients" << std::endl;
        clear_all_clients();
        std::cout << "Server Closed" << std::endl;
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in matches manager: " << err.what() << "\n";
            stop();
        }
    }
}

void MatchesManager::create_new_match(const CreateGameDTO& dto) {
    matches_number++;
    std::cout << "creating new match " << matches_number << std::endl;
    auto match =
            std::make_shared<Match>(dto.map_name, dto.max_players, manager_queue, client_monitor);
    matches.insert({matches_number, match});

    auto match_added = matches.find(matches_number)->second.get();

    auto client = get_client_by_id(dto.id_client);
    client->set_match_joined_id(matches_number);
    //    client->set_receiver_queue(match_added->get_match_queue());
    client_monitor.addClient(client->get_sender_queue());

    match->start();

    std::string namestr = "Player 1";
    auto message =
            make_add_player_message(namestr, dto.id_client, dto.character_selected, dto.map_name);
    match_added->get_match_queue().try_push(message);

    send_client_succesful_connect(dto.id_client, dto.map_name);
    //    match->add_client_to_match(get_client_by_id(dto.id_client), "jugador_1_creador",
    //                               dto.character_selected);
}

void MatchesManager::send_client_succesful_connect(const uint16_t& id_client,
                                                   const map_list_t& map) {
    ClientHasConnectedToMatchDTO game_connected = {map};
    auto send_game_created = std::make_shared<SendConnectedToGameMessage>(game_connected);
    get_client_by_id(id_client)->get_sender_queue()->push(send_game_created);
}

void MatchesManager::join_match(const JoinMatchDTO& dto) {
    std::cout << "Joining match id " << dto.id_match << std::endl;
    auto it = matches.find(dto.id_match);
    if (it != matches.end()) {
        std::cout << "match found to join " << std::endl;
        auto client = get_client_by_id(dto.id_client);
        client->set_match_joined_id(dto.id_match);
        auto map = it->second->get_map();
        client_monitor.addClient(client->get_sender_queue());
        std::string namestr = "Player " + std::to_string(dto.id_client);
        auto message = make_add_player_message(namestr, dto.id_client, dto.player_character, map);
        it->second->get_match_queue().try_push(message);
        send_client_succesful_connect(dto.id_client, map);
        //        it->second->add_client_to_match(get_client_by_id(dto.id_client), "pepo_joineado",
        //                                        dto.player_character);
    }
}

std::shared_ptr<AddPlayerMessage> MatchesManager::make_add_player_message(
        const std::string& player_name, id_client_t id_client, character_t character,
        map_list_t map) const {
    AddPlayerDTO AddDTO = {};
    snprintf(AddDTO.name, sizeof(AddDTO.name), "%s", player_name.c_str());
    AddDTO.id_client = id_client;
    AddDTO.player_character = character;
    AddDTO.map_name = map;
    return std::make_shared<AddPlayerMessage>(AddDTO);
}

ServerThreadManager* MatchesManager::get_client_by_id(const size_t& id) {
    auto it = std::find_if(clients.begin(), clients.end(), [id](ServerThreadManager* client) {
        return client->get_client_id() == id;
    });
    return (it != clients.end()) ? *it : nullptr;
}

void MatchesManager::add_new_client_to_manager(Socket client_socket) {
    clients_connected++;
    auto client = new ServerThreadManager(std::move(client_socket), manager_queue);
    auto message = std::make_shared<AcptConnection>(clients_connected);  // le mando su id
    client->get_sender_queue()->push(message);
    client->set_client_id(clients_connected);
    clients.push_back(client);
    std::cout << "Client " << clients_connected << " connected to server." << std::endl;
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

void MatchesManager::delete_disconnected_client(const id_client_t& id_client) {
    for (auto client = clients.begin(); client != clients.end(); ++client) {
        if (id_client == (*client)->get_client_id()) {
            std::cout << "Stopping client " << id_client << " in lobby." << std::endl;
            client_monitor.removeQueue(get_client_by_id(id_client)->get_sender_queue());
            (*client)->stop();
            delete *client;
            clients.erase(client);
            std::cout << "Client " << id_client << " disconnected from lobby." << std::endl;
            break;
        }
    }
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
    std::vector<size_t> ids = match->get_clients_ids();
    match->stop();
    match->join();
    for (auto id: ids) {
        auto it = clients.begin();
        while (it != clients.end()) {
            if ((*it)->get_client_id() == id) {
                //                (*it)->set_receiver_queue(nullptr);
                //                (*it)->set_receiver_queue(manager_queue);
                break;
            } else {
                ++it;
            }
        }
    }
}

void MatchesManager::clear_all_clients() {
    for (auto& client: clients) {
        //        CloseConnectionDTO close_connection{client->get_client_id()};
        //        auto game_ended_message =
        //        std::make_shared<CloseConnectionMessage>(close_connection);
        //        client->get_sender_queue()->try_push(game_ended_message);
        client->stop();
        delete client;
    }
    clients.clear();
}

void MatchesManager::stop_all_matches() {
    for (auto& match: matches) {
        std::cout << "Stopping match " << match.first << std::endl;
        stop_finished_match(match.second.get());
        //        match.second->stop();
        //        match.second->join();
    }
    matches.clear();
}

void MatchesManager::stop() { online = false; }

Queue<std::shared_ptr<Message>>& MatchesManager::get_match_queue_by_id(size_t i) {
    auto it = matches.find(i);
    if (it != matches.end()) {
        return it->second->get_match_queue();
    } else {
        throw std::runtime_error("Match with the given ID not found.");
    }
}
