#ifndef TP_FINAL_CLIENT_H
#define TP_FINAL_CLIENT_H

#include <atomic>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../game_engine/gui/basic/resource_pool.h"
#include "../game_engine/gui/basic/window.h"
#include "../game_engine/gui/canvas_object.h"
#include "../game_engine/gui/widgets/animated_sprite.h"
#include "game_objects/player.h"
#include "protocol/client_protocol.h"
#include "protocol/client_thread_manager.h"

#include "event_loop.h"
// #include "../common/common_queue.h"

#define QUIT 'q'

class Client {
private:
    Queue<std::shared_ptr<Message>> recv_message;
    EventLoop event_loop;
    std::atomic<bool> game_running;
    ClientThreadManager thread_manager;

public:
    Client(const std::string& host, const std::string& port);

    void start();

    ~Client();
};


#endif  // TP_FINAL_CLIENT_H
