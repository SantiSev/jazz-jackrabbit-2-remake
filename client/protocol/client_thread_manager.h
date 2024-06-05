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

public:
    ClientThreadManager(const std::string& hostname, const std::string& servname,
                        Queue<std::shared_ptr<Message>>& receiver_queue,
                        Queue<std::shared_ptr<Message>>& sender_queue);

    void set_active_games(MatchInfoDTO dto);

    ~ClientThreadManager();

    ClientProtocol& get_protocol();
};


#endif
