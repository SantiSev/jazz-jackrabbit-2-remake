#ifndef TP_FINAL_CLIENT_H
#define TP_FINAL_CLIENT_H

#include <atomic>
#include <iostream>
#include <list>
#include <string>

#include <SDL2/SDL.h>

#include "../game_engine/gui/basic/resource_pool.h"
#include "../game_engine/gui/basic/window.h"
#include "../game_engine/gui/canvas_object.h"
#include "../game_engine/gui/widgets/animated_sprite.h"
//#include "protocol/client_protocol.h"
#include <utility>

#include "game_objects/player.h"

#include "event_loop.h"
//#include "../common/common_queue.h"

#define QUIT 'q'

class Client {
private:
    // ClientProtocol protocol;
    // Queue<std::string> messages;

    std::atomic<bool> game_running;
    EventLoop event_loop;

public:
    Client(const std::string& host, const std::string& port);

    void start();

    ~Client();
};


#endif  // TP_FINAL_CLIENT_H
