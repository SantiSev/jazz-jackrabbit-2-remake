#ifndef TP_FINAL_MATCHES_MANAGER_H
#define TP_FINAL_MATCHES_MANAGER_H

#include <cstdio>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../protocol/manager_message_handler.h"
#include "../protocol/server_thread_manager.h"
#include "./match.h"

class Message;

class MatchesManager: public Thread {
private:
    bool online = true;
    uint16_t clients_connected = 0;
    int matches_number = 0;
    std::map<int, std::shared_ptr<Match>> matches;
    std::list<ServerThreadManager*> clients;
    MatchesManagerMessageHandler message_handler;
    std::mutex manager_mutex;
    std::map<int, ClientMonitor*> client_monitors;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    void pre_load_resources();

public:
    Queue<std::shared_ptr<Message>> manager_queue;

    MatchesManager();

    void run() override;
    void stop() override;
    ~MatchesManager() override = default;

    void add_new_client_to_manager(Socket client_socket);
    void create_new_match(const CreateGameDTO& dto);
    void join_match(const JoinMatchDTO& dto);
    void send_client_succesful_connect(const uint16_t& id_client, const map_list_t& map);
    void send_match_lists(RequestActiveGamesDTO dto);

    MatchInfoDTO return_matches_lists();
    void stop_all_matches();
    void clear_all_clients();
    void check_matches_status();
    void delete_disconnected_client(const id_client_t& id_client);

    ServerThreadManager* get_client_by_id(const uint16_t& id);
    std::shared_ptr<AddPlayerMessage> make_add_player_message(const std::string& player_name,
                                                              id_client_t client_id,
                                                              character_t character,
                                                              map_list_t map) const;
    Queue<std::shared_ptr<Message>>& get_match_queue_by_id(int match_id);
    void clean_client_monitors();
};

#endif
