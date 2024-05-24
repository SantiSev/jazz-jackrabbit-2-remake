#ifndef TP_FINAL_SERVER_EVENTLOOP_H
#define TP_FINAL_SERVER_EVENTLOOP_H

#include <string>

#include "../common/common_constants.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"

class Server_Eventloop: public Thread {
private:
    bool online;
    Queue<std::string>& event_queue;    // COMPARTIDA CON EL SERVER_RECEIVER
    Queue<std::string>& command_queue;  // COMPARTIDA CON GAMELOOP

public:
    // Constructor
    Server_Eventloop(Queue<std::string>& eventQueue, Queue<std::string>& commandQueue);

    void run() override;
    // Kill the thread
    void stop() override;
    // Destroyer
    ~Server_Eventloop() override = default;

    void compute_command(std::string basic_string);

    void filter_command_type(uint8_t basicString);
};


#endif
