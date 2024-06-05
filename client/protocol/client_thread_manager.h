#ifndef TP_FINAL_CLIENT_THREAD_MANAGER_H
#define TP_FINAL_CLIENT_THREAD_MANAGER_H

#include <memory>
#include <string>

#include "./client_protocol.h"
#include "./client_receiver.h"
#include "./client_sender.h"

#include "client_message_handler.h"

class ClientThreadManager {
private:
    ClientProtocol client_protocol;
    ClientReceiver receiver;
    ClientSender sender;
    id_client_t my_client_id;
    id_player_t my_player_id;
    ClientMessageHandler message_handler;

public:
    ClientThreadManager(const std::string& hostname, const std::string& servname,
                        Queue<std::shared_ptr<Message>>& receiver_queue,
                        Queue<std::shared_ptr<Message>>& sender_queue);

    void set_my_client_id(const id_client_t& new_client_id);

    uint16_t get_client_id() const;

    void set_my_player_id(const id_player_t& new_player_id);

    uint16_t get_player_id() const;

    void set_active_games(MatchInfoDTO dto);

    ~ClientThreadManager();

    ClientProtocol& get_protocol();
};


#endif
