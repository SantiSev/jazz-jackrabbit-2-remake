#ifndef TP_FINAL_MATCHES_MANAGER_H
#define TP_FINAL_MATCHES_MANAGER_H

#include <cstdio>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../common/common_thread.h"
#include "../match.h"
#include "../protocol/server_thread_manager.h"

class MatchesManager: public Thread {
private:
    bool online = true;
    size_t clients_connected = 0;
    size_t matches_number = 0;
    std::map<size_t, std::shared_ptr<Match>> matches;
    std::list<ServerThreadManager*> clients;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> waiting_server_queue;

public:
    MatchesManager();

    void run() override;
    void stop() override;
    ~MatchesManager() = default;

    void stop_all_matches();
    void check_matches_status();
    void stop_finished_match(Match* match);
    void add_player_to_game(Player& player, size_t match_id);

    std::vector<matchesDTO> return_matches_lists();

    void create_new_match(ServerThreadManager* client, const std::shared_ptr<Message>& message);

    void add_new_client(Socket client_socket);

    void send_match_lists(TestClientServer* client);

    void clear_all_waiting_clients();

    void join_match(TestClientServer* client, const std::shared_ptr<Message>& message);
};


#endif
