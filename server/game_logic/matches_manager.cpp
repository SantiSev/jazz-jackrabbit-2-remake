#include "matches_manager.h"

#include <memory>
#include <utility>
#include <vector>

#include "../../common/common_socket.h"

MatchesManager::MatchesManager():
        online(true),
        matches_number(0),
        waiting_server_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()) {}

void MatchesManager::run() {
    try {
        Socket skt("8081");
        add_new_client(std::move(skt));
        create_new_match(clients.front(), nullptr);
        std::shared_ptr<Message> client_message;
        while (online) {
            check_matches_status();

            while (waiting_server_queue->try_pop(client_message)) {}

            client_message->run();


            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        clear_all_waiting_clients();
        stop_all_matches();
        waiting_server_queue->close();
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

void MatchesManager::create_new_match(TestClientServer* client,
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
            it = matches.erase(it);
        } else {
            ++it;
        }
    }
}

void MatchesManager::stop_finished_match(Match* match) {
    match->stop();
    match->join();
}

void MatchesManager::stop_all_matches() {
    for (auto it = matches.begin(); it != matches.end();) {
        if (matches.empty())
            break;
        it->second->stop();
        it->second->join();
        //        it->second.reset();
        matches.erase(it);
    }
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
    auto client = new TestClientServer(std::move(client_socket), waiting_server_queue);
    client->start();
    //    auto message =std::make_shared<ConnectedMessage>(clients_connected);  // le mando su id
    //    para que lo guarde client->get_sender_queue()->push(message);
    clients.push_back(client);
}

void MatchesManager::send_match_lists(TestClientServer* client) {
    // todo deberia ser así
    // client->get_sender_queue()->push(return_matches_lists());
}

void MatchesManager::stop() { online = false; }

void MatchesManager::clear_all_waiting_clients() {
    for (auto& client: clients) {
        client->stop();
    }
    for (auto& client: clients) {
        delete client;
    }
    clients.clear();
}
