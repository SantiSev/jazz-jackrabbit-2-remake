#include <memory>
#include <string>

#include "./client_receiver.h"
#include "./client_sender.h"

class ClientThreadManager {
private:
    ClientProtocol client_protocol;
    ClientReceiver receiver;
    ClientSender sender;

public:
    ClientThreadManager(const std::string& hostname, const std::string& servname,
                        Queue<std::unique_ptr<Message>>& queue);
    ~ClientThreadManager();
};
