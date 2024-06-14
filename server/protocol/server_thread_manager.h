#ifndef _SERVER_THREAD_MANAGER_H
#define _SERVER_THREAD_MANAGER_H
#include <memory>

#include "./server_receiver.h"
#include "./server_sender.h"

class ServerThreadManager {
private:
    ServerProtocol server_protocol;
    ServerReceiver receiver;
    ServerSender sender;
    id_client_t client_id = 0;
    int match_joined_id = 0;

public:
    ServerThreadManager(Socket&& skt, Queue<std::shared_ptr<Message>>& receiver_queue);

    std::shared_ptr<Queue<std::shared_ptr<Message>>>& get_sender_queue();

    void set_client_id(const uint16_t& new_id);

    id_client_t get_client_id() const;

    void stop();

    ~ServerThreadManager();

    int get_current_match_id() const;

    void set_match_joined_id(const int& new_id);
};

#endif
