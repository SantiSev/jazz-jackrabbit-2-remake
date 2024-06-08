#ifndef TP_FINAL_MATCHES_MANAGER_H
#define TP_FINAL_MATCHES_MANAGER_H

#include <cstdio>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../protocol/manager_message_handler.h"
#include "../protocol/server_thread_manager.h"
#include "./match.h"

class Message;

class MatchesManager: public Thread {
private:
    bool online = true;
    size_t clients_connected = 0;
    size_t matches_number = 0;
    std::map<size_t, std::shared_ptr<Match>> matches;
    std::list<ServerThreadManager*> clients;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> waiting_server_queue;
    MatchesManagerMessageHandler message_handler;

public:
    MatchesManager();

    void run() override;
    void stop() override;
    ~MatchesManager() override = default;

    void stop_all_matches();
    void check_matches_status();
    void stop_finished_match(Match* match);

    MatchInfoDTO return_matches_lists();

    void create_new_match(const CreateGameDTO& dto);

    void add_new_client_to_manager(Socket client_socket);

    void send_match_lists(RequestActiveGamesDTO dto);

    void clear_all_clients();

    void join_match(const JoinMatchDTO& dto);

    ServerThreadManager* get_client_by_id(size_t id);

    void send_client_succesful_connect(uint16_t id_client);

    void delete_disconnected_client(id_client_t id_client);
};


#endif
