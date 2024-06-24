#ifndef TP_FINAL_MATCH_SELECT_SCENE_H
#define TP_FINAL_MATCH_SELECT_SCENE_H

#include <list>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/sound_manager.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../event_loop.h"
#include "../menu_objects/match_selector.h"
#include "../menu_objects/receive_matches_button.h"
#include "../protocol/client_message_handler.h"
#include "../shared/background.h"

#include "character_select_scene.h"
#include "map_select_scene.h"

class MatchSelectScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::shared_ptr<engine::SoundManager> sound_manager;
    std::unique_ptr<engine::CanvasObject> background;
    std::list<engine::Button*> buttons;
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;
    std::atomic<bool>& match_select_running;
    std::atomic<bool> character_select_running;
    std::atomic<bool> match_requested;

    ClientMessageHandler& message_handler;
    Queue<std::shared_ptr<MatchInfoDTO>> match_select_q;
    uint16_t selected_id;

    void create_buttons();

public:
    MatchSelectScene(engine::Window& window, EventLoop* event_loop,
                     std::shared_ptr<engine::ResourcePool> resource_pool,
                     std::shared_ptr<engine::SoundManager> sound_manager,
                     std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     std::atomic<bool>& match_select_running,
                     ClientMessageHandler& message_handler);

    // cant copy
    MatchSelectScene(const MatchSelectScene&) = delete;
    MatchSelectScene& operator=(const MatchSelectScene&) = delete;

    void start();

    ~MatchSelectScene();

    void show_matches();

    void create_match_buttons(std::shared_ptr<MatchInfoDTO> sharedPtr);
};


#endif
