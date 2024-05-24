#ifndef TP_FINAL_SERVER_H
#define TP_FINAL_SERVER_H


#include <string>

class Server {
private:
    std::string portDir;

public:
    // Constructor of the Server class, initializes the protocol and receives the port as a
    // parameter to create the socket
    explicit Server(const std::string& port);
    // Run the server, creates and throws two threads, the accepter and the gameloop (logic of the
    // game), then waits for the user to close the server
    void run();
    // Returns the name of the port
    const std::string& get_servname();
    // Destroyer
    ~Server();
};


#endif
