#include "matches_manager.h"

#include <vector>

#include "snapshot.h"

MatchesManager::MatchesManager() {}

void MatchesManager::run() {
    try {
        //        add_match("my first match");

        matches_number++;
        Queue<Message*> event_queue(0);
        Queue<Snapshot> snapshot_queue;
        Server_Gameloop gameloop(event_queue, snapshot_queue, "my first match",
                                 REQUIRED_PLAYERS_TO_START);
        matches.insert({matches_number, gameloop});
        gameloop.start();

        while (online) {
            check_matches_status();

            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            Player player(0, "jorge", "guerrero");
            add_player_to_game(player, matches_number);
        }
        gameloop.stop();
        gameloop.join();
        //        stop_all_matches();
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

void MatchesManager::add_match(const std::string& name) {
    //    matches_number++;
    //    auto event_queue = std::make_shared<Queue<Message *>>(0);
    //    auto snapshot_queue = std::make_shared<Queue<Snapshot>>();
    //    auto gameloop = std::make_shared<Server_Gameloop>(*event_queue, *snapshot_queue, name);
    //    matches.insert({matches_number, gameloop});
    //    gameloop->start();
}

void MatchesManager::check_matches_status() {
    //    for (auto it = matches.begin(); it != matches.end(); ) {
    //        if (it->second->has_match_ended()) {
    //            std::cout << "Match " << it->first << " " << it->second->get_match_name() << " has
    //            ended.\n"; stop_finished_match(it->second.get()); it = matches.erase(it);
    //        } else {
    //            ++it;
    //        }
    //    }
}

void MatchesManager::stop_finished_match(Server_Gameloop* match) {
    match->stop();
    match->join();
}

void MatchesManager::stop_all_matches() {
    //    for (auto it = matches.begin(); it != matches.end(); ) {
    //        if (matches.empty())
    //            break;
    //        it->second->stop();
    //        it->second->join();
    //        it->second.reset();
    //        matches.erase(it);
    //    }
}

std::vector<matchesDTO> MatchesManager::return_matches_lists() {
    std::vector<matchesDTO> matches_list;
    for (auto& matche: matches) {
        matchesDTO match;
        match.match_name = matche.second.get_match_name();
        match.match_id = matche.first;
        match.minutes = matche.second.get_minutes();
        match.seconds = matche.second.get_seconds();
        match.num_actual_players = matche.second.get_num_players();
        match.max_players = matche.second.get_max_players();
        matches_list.push_back(match);
    }
    return matches_list;
}

void MatchesManager::add_player_to_game(Player& player, size_t match_id) {
    auto it = matches.find(match_id);
    if (it != matches.end()) {
        it->second.add_player_to_game(player);
    }
}

void MatchesManager::stop() { online = false; }
