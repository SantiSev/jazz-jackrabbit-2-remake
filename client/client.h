#ifndef TP_FINAL_CLIENT_H
#define TP_FINAL_CLIENT_H

#include <algorithm>
#include <atomic>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../common/assets.h"
#include "../common/character_enum.h"
#include "../common/common_queue.h"
#include "../common/item_enum.h"
#include "../common/map_enum.h"
#include "../common/sfx_enum.h"
#include "../common/sound_enum.h"
#include "../game_engine/gui/basic/resource_pool.h"
#include "../game_engine/gui/basic/window.h"
#include "../game_engine/gui/canvas_object.h"
#include "../game_engine/gui/widgets/animated_sprite.h"
#include "../game_engine/gui/widgets/sound_manager.h"
#include "game_objects/player_controller.h"
#include "protocol/client_protocol.h"
#include "protocol/client_thread_manager.h"
#include "protocol/message_runner.h"
#include "scenes/match_scene.h"
#include "scenes/menu_scene.h"

#include "event_loop.h"

#define CONFIG_FILE "assets/config.yaml"

class Client {
private:
    engine::Window window;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    std::atomic<bool> game_running;
    std::atomic<bool> menu_running;
    std::atomic<bool> match_running;

    std::atomic<map_list_t> map_enum;
    std::atomic<id_client_t> id_client;

    ClientMessageHandler message_handler;
    EventLoop* event_loop;
    MessageRunner* message_runner;
    ClientThreadManager* thread_manager;
    std::shared_ptr<engine::SoundManager> sound_manager;

    void pre_load_resources();

    friend class ClientMessageHandler;

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
