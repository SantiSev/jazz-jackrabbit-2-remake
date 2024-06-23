#include "matches_manager.h"

#include <memory>
#include <utility>
#include <vector>

MatchesManager::MatchesManager():
        online(true),
        matches_number(0),
        message_handler(*this, manager_queue),
        client_monitors(),
        resource_pool(std::make_shared<engine::ResourcePool>()),
        manager_queue(Queue<std::shared_ptr<Message>>()) {
    pre_load_resources();
}


void MatchesManager::run() {
    try {
        while (online) {
            std::shared_ptr<Message> client_message = nullptr;
            size_t events = 0;
            while (manager_queue.try_pop(client_message) && events < MAX_EVENTS_PER_LOOP) {
                events++;
                if (client_message) {
                    client_message->run(message_handler);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
#ifdef LOG_VERBOSE
        std::cout << "stopping matches" << std::endl;
#endif
        stop_all_matches();
#ifdef LOG_VERBOSE
        std::cout << "clearing all clients" << std::endl;
#endif
        clear_all_clients();
#ifdef LOG_VERBOSE
        std::cout << "cleaning monitors" << std::endl;
#endif
        clean_client_monitors();
#ifdef LOG_VERBOSE
        std::cout << "Server Closed" << std::endl;
#endif
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in matches manager: " << err.what() << "\n";
            stop();
        }
    }
}

void MatchesManager::create_new_match(const CreateGameDTO& dto) {
    auto config = resource_pool->get_config();
    if (!can_create_match(config->match_max_matches)) {
        return;
    }
    matches_number++;

    auto new_monitor = new ClientMonitor();
    client_monitors.insert({matches_number, new_monitor});
    auto match = std::make_shared<Match>(dto.map_name, config->match_max_players, manager_queue,
                                         *new_monitor, resource_pool);

    matches[matches_number] = match;
    match->start();

    auto client = get_client_by_id(dto.id_client);
    client->set_match_joined_id(matches_number);
    new_monitor->addClient(client->get_sender_queue());

    std::string namestr = "Player " + std::to_string(dto.id_client);
    auto message =
            make_add_player_message(namestr, dto.id_client, dto.character_selected, dto.map_name);
    match->match_queue.try_push(message);

    send_client_succesful_connect(dto.id_client, dto.map_name);
}

void MatchesManager::send_client_succesful_connect(const uint16_t& id_client,
                                                   const map_list_t& map) {
    ClientHasConnectedToMatchDTO game_connected = {map};
    auto send_game_created = std::make_shared<SendConnectedToGameMessage>(game_connected);
    get_client_by_id(id_client)->get_sender_queue().push(send_game_created);
}

void MatchesManager::join_match(const JoinMatchDTO& dto) {
#ifdef LOG_VERBOSE
    std::cout << "Joining match id " << dto.id_match << std::endl;
#endif
    auto it = matches.find(dto.id_match);
    if (it != matches.end()) {
#ifdef LOG_VERBOSE
        std::cout << "match found to join " << std::endl;
#endif
        auto client = get_client_by_id(dto.id_client);
        client->set_match_joined_id(dto.id_match);
        auto map = it->second->get_map();
        auto monitor = client_monitors.find(dto.id_match)->second;
        monitor->addClient(client->get_sender_queue());

        std::string namestr = "Player " + std::to_string(dto.id_client);
        auto message = make_add_player_message(namestr, dto.id_client, dto.player_character, map);
        it->second->match_queue.try_push(message);

        send_client_succesful_connect(dto.id_client, map);
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

ServerThreadManager* MatchesManager::get_client_by_id(const uint16_t& id) {
    auto it = std::find_if(clients.begin(), clients.end(), [id](ServerThreadManager* client) {
        return client->get_client_id() == id;
    });
    return (it != clients.end()) ? *it : nullptr;
}

void MatchesManager::add_new_client_to_manager(Socket client_socket) {
    std::unique_lock<std::mutex> lock(manager_mutex);
    client_id_counter++;
    auto client = new ServerThreadManager(std::move(client_socket), manager_queue);
    auto message = std::make_shared<AcptConnection>(client_id_counter);  // le mando su id
    client->get_sender_queue().push(message);
    client->set_client_id(client_id_counter);
    client->set_match_joined_id(0);
    clients.push_back(client);
#ifdef LOG_VERBOSE
    std::cout << "Client " << client_id_counter << " connected to server." << std::endl;
#endif
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
    std::unique_lock<std::mutex> lock(manager_mutex);
    auto matches_lists = return_matches_lists();
    auto matches_message = std::make_shared<RecvActiveGames>(matches_lists);
    get_client_by_id(dto.id_client)->get_sender_queue().push(matches_message);
}

void MatchesManager::delete_disconnected_client(const id_client_t& id_client) {
    std::unique_lock<std::mutex> lock(manager_mutex);
    for (auto client = clients.begin(); client != clients.end(); ++client) {
        if (id_client == (*client)->get_client_id()) {
#ifdef LOG_VERBOSE
            std::cout << "Stopping client " << id_client << " in lobby." << std::endl;
#endif
            CloseConnectionDTO dto = {id_client};
            if ((*client)->get_current_match_id() != 0) {
                matches.at((*client)->get_current_match_id())
                        ->match_queue.push(std::make_shared<CloseConnectionMessage>(dto));
                client_monitors.find((*client)->get_current_match_id())
                        ->second->removeQueue((*client)->get_sender_queue());
            }
            (*client)->stop();
            delete *client;
            clients.erase(client);
#ifdef LOG_VERBOSE
            std::cout << "Client " << id_client << " disconnected from lobby." << std::endl;
#endif
            break;
        }
    }
}

void MatchesManager::check_matches_status() {
    std::unique_lock<std::mutex> lock(manager_mutex);
    for (auto it = matches.begin(); it != matches.end();) {
        if (it->second->has_match_ended()) {
#ifdef LOG_VERBOSE
            std::cout << "Match " << it->first << " map " << it->second->get_map()
                      << " has ended.\n";
#endif
            auto ids = it->second->get_clients_ids();
            for (auto id: ids) {
                get_client_by_id(id)->set_match_joined_id(0);
                get_client_by_id(id)->get_sender_queue().push(
                        std::make_shared<SendFinishMatchMessage>());
            }
            it->second->stop();
            it->second->join();
            matches.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

void MatchesManager::clear_all_clients() {
    std::unique_lock<std::mutex> lock(manager_mutex);
    for (auto& client: clients) {
        CloseConnectionDTO close_connection{};
        auto game_ended_message = std::make_shared<CloseConnectionMessage>(close_connection);
        client->get_sender_queue().try_push(game_ended_message);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        client->stop();
        delete client;
    }
    clients.clear();
}

void MatchesManager::stop_all_matches() {
    std::unique_lock<std::mutex> lock(manager_mutex);
    for (auto& match: matches) {
#ifdef LOG_VERBOSE
        std::cout << "Stopping match " << match.first << std::endl;
#endif
        match.second->stop();
        match.second->join();
    }
    matches.clear();
}

void MatchesManager::pre_load_resources() {
    resource_pool->load_yaml(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(MAD_HATTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LIZARD_GOON));
    resource_pool->load_yaml(SFX_FILE);
    resource_pool->load_yaml(map_list_to_string.at(MAP_1));
    resource_pool->load_yaml(CONFIG);
    resource_pool->load_config(CONFIG);
}

void MatchesManager::stop() { online = false; }

Queue<std::shared_ptr<Message>>& MatchesManager::get_match_queue_by_id(int match_id) {
    auto it = matches.find(match_id);
    if (it != matches.end()) {
        return it->second->get_match_queue();
    } else {
        throw std::runtime_error("Match with the given ID not found.");
    }
}

void MatchesManager::clean_client_monitors() {
    for (auto monitor: client_monitors) {
        delete (monitor.second);
    }
    client_monitors.clear();
}

bool MatchesManager::can_create_match(int max_matches) { return matches_number < max_matches; }
