#ifndef TP_FINAL_MATCH_SELECT_SCENE_H
#define TP_FINAL_MATCH_SELECT_SCENE_H

#include <functional>
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
#include "../menu_objects/return_to_menu.h"
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
    std::unique_ptr<engine::CanvasObject> background;
    engine::Label title;
    engine::ColorRect title_background;
    std::shared_ptr<engine::SoundManager> sound_manager;
    std::list<engine::Button*> buttons;
    std::list<MatchSelector> selectors;
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;
    std::atomic<bool>& match_select_running;
    std::atomic<bool>& character_select_running;
    std::atomic<bool> match_requested;
    std::atomic<bool>& is_joinning;

    ClientMessageHandler& message_handler;
    Queue<std::shared_ptr<MatchInfoDTO>> match_select_q;
    uint16_t& selected_id;

    void create_buttons();

public:
    MatchSelectScene(engine::Window& window, EventLoop* event_loop,
                     std::shared_ptr<engine::ResourcePool> resource_pool,
                     std::shared_ptr<engine::SoundManager> sound_manager,
                     std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     std::atomic<bool>& match_select_running, std::atomic<bool>& is_joinning,
                     std::atomic<bool>& character_select_running,
                     ClientMessageHandler& message_handler, uint16_t& joined_id_match);

    // cant copy
    MatchSelectScene(const MatchSelectScene&) = delete;
    MatchSelectScene& operator=(const MatchSelectScene&) = delete;

    void start();

    ~MatchSelectScene();

    void show_matches();

    void create_match_buttons(const std::shared_ptr<MatchInfoDTO>& sharedPtr);

    void clear_list_buttons();

    std::string get_map_name(int map_id);
};


#endif
