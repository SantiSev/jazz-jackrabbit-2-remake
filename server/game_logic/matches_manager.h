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
    MatchesManagerMessageHandler message_handler;
    std::mutex manager_mutex;
    ClientMonitor client_monitor;

public:
    Queue<std::shared_ptr<Message>> manager_queue;

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

    ServerThreadManager* get_client_by_id(const size_t& id);

    void send_client_succesful_connect(const uint16_t& id_client, const map_list_t& map);

    void delete_disconnected_client(const id_client_t& id_client);

    std::shared_ptr<AddPlayerMessage> make_add_player_message(const std::string& player_name,
                                                              id_client_t client_id,
                                                              character_t character,
                                                              map_list_t map) const;

    Queue<std::shared_ptr<Message>>& get_match_queue_by_id(size_t i);
};


#endif
