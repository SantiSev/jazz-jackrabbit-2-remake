#ifndef TP_FINAL_MENU_H
#define TP_FINAL_MENU_H

#include <list>
#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../event_loop.h"
#include "../menu_objects/create_match_button.h"
#include "../menu_objects/editor_button.h"
#include "../menu_objects/join_match_button.h"
#include "../menu_objects/quit_button.h"
#include "../protocol/client_message_handler.h"
#include "../shared/background.h"

#include "character_select_scene.h"


class MenuScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::unique_ptr<engine::CanvasObject> background;
    std::list<engine::Button*> buttons;
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;
    std::atomic<bool>& editor_running;
    std::atomic<bool> character_select_running;

    ClientMessageHandler& message_handler;

    void create_buttons();

public:
    MenuScene(engine::Window& window, EventLoop* event_loop,
              std::shared_ptr<engine::ResourcePool> resource_pool, std::atomic<bool>& game_running,
              std::atomic<bool>& menu_running, std::atomic<bool>& editor_running,
              ClientMessageHandler& message_handler);

    // cant copy
    MenuScene(const MenuScene&) = delete;
    MenuScene& operator=(const MenuScene&) = delete;

    void start();

    ~MenuScene();
};


#endif  // TP_FINAL_MENU_H
