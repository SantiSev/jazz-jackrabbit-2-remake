#ifndef TP_FINAL_MATCHES_MANAGER_H
#define TP_FINAL_MATCHES_MANAGER_H


#include <cstdio>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../common/common_thread.h"
#include "../server_gameloop.h"
#include "../test_client_server.h"

class MatchesManager: public Thread {
private:
    std::map<size_t, std::shared_ptr<ServerGameloop>> matches;
    //    std::map<size_t, Server_Gameloop&> matches;
    bool online = true;
    size_t matches_number = 0;

public:
    MatchesManager();

    void run() override;
    void add_match(const std::string& name);
    void stop() override;
    ~MatchesManager() = default;


    void stop_all_matches();

    void check_matches_status();

    void stop_finished_match(ServerGameloop* match);

    void add_player_to_game(Player& player, size_t match_id);

    std::vector<matchesDTO> return_matches_lists();
};


#endif
