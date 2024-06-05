#ifndef TP_FINAL_MENU_H
#define TP_FINAL_MENU_H

#include <list>
#include <memory>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../assets.h"
#include "../event_loop.h"
#include "../menu_objects/create_match_button.h"
#include "../menu_objects/join_match_button.h"
#include "../menu_objects/quit_button.h"
#include "../protocol/client_message_handler.h"

class Menu {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    engine::Sprite* background;
    std::list<engine::Button*> buttons;
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;

public:
    Menu(engine::Window& window, EventLoop* event_loop,
         std::shared_ptr<engine::ResourcePool> resource_pool, std::atomic<bool>& game_running,
         std::atomic<bool>& menu_running, ClientMessageHandler& message_handler);

    // cant copy
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    void start();

    ~Menu();
};


#endif  // TP_FINAL_MENU_H
