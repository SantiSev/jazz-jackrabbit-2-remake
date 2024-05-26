#include "matches_manager.h"

#include <memory>
#include <vector>

#include "snapshot.h"

MatchesManager::MatchesManager() {}

void MatchesManager::run() {
    try {
        add_match("my first match");
        while (online) {
            check_matches_status();

            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            //            Player player(0, "jorge", "guerrero");
            //            add_player_to_game(player, matches_number);
        }
        stop_all_matches();
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

// void create_new_match(TestClientServer client, std::shared_ptr<Message> message) {
//     std::shared_ptr<Server_Gameloop> gameloop =
//     std::dynamic_pointer_cast<Server_Gameloop>(message);
// }

void MatchesManager::add_match(const std::string& name) {
    matches_number++;
    auto event_queue = std::make_shared<Queue<std::shared_ptr<Message>>>(0);
    auto snapshot_queue = std::make_shared<Queue<Snapshot>>();
    auto gameloop = std::make_shared<ServerGameloop>(event_queue, snapshot_queue, name,
                                                     REQUIRED_PLAYERS_TO_START);
    matches.insert({matches_number, gameloop});
    gameloop->start();
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

void MatchesManager::stop_finished_match(ServerGameloop* match) {
    match->stop();
    match->join();
}

void MatchesManager::stop_all_matches() {
    for (auto it = matches.begin(); it != matches.end();) {
        if (matches.empty())
            break;
        it->second->stop();
        it->second->join();
        it->second.reset();
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
    auto it = matches.find(match_id);
    if (it != matches.end()) {
        it->second->add_player_to_game(player);
    }
}

void MatchesManager::stop() { online = false; }
