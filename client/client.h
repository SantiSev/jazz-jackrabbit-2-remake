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
#include "scenes/menu.h"

#include "assets.h"
// #include "protocol/client_protocol.h"
#include <memory>
#include <utility>

#include "game_objects/player.h"

#include "event_loop.h"
// #include "../common/common_queue.h"

#define QUIT 'q'

class Client {
private:
    // ClientProtocol protocol;
    // Queue<std::string> messages;

    engine::Window window;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    std::atomic<bool> game_running;
    std::atomic<bool> menu_running;

    EventLoop* event_loop;

    void pre_load_resources(std::shared_ptr<engine::ResourcePool>& resource_pool);

public:
    Client(const std::string& host, const std::string& port);

    // cant copy or move
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    void start();

    ~Client();
};


#endif  // TP_FINAL_CLIENT_H
