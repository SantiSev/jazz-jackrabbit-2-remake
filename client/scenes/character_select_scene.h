#ifndef TP_FINAL_CHARACTER_SELECT_H
#define TP_FINAL_CHARACTER_SELECT_H

#include <list>
#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../common/sound_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/color_rect.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../../game_engine/gui/widgets/sound_manager.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../event_loop.h"
#include "../menu_objects/character_selector.h"
#include "../protocol/client_message_handler.h"
#include "../shared/background.h"


class CharacterSelectScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::shared_ptr<engine::SoundManager> sound_manager;
    std::unique_ptr<engine::CanvasObject> background;
    engine::Label title;
    engine::ColorRect title_background;
    std::list<CharacterSelector> selectors;

    std::atomic<bool>& game_running;
    std::atomic<bool>& character_select_running;
    uint16_t& match_selected_id;
    std::atomic<bool>& is_joinning;

    ClientMessageHandler& message_handler;

    void create_buttons();

public:
    character_t selected_character;

    CharacterSelectScene(engine::Window& window, EventLoop* event_loop,
                         std::shared_ptr<engine::ResourcePool> resource_pool,
                         std::shared_ptr<engine::SoundManager> sound_manager,
                         std::atomic<bool>& game_running,
                         std::atomic<bool>& character_select_running,
                         std::atomic<bool>& is_joinning, uint16_t& match_selected_id,
                         ClientMessageHandler& message_handler);

    // cant copy
    CharacterSelectScene(const CharacterSelectScene&) = delete;
    CharacterSelectScene& operator=(const CharacterSelectScene&) = delete;

    void start(uint16_t selected_map_id);

    ~CharacterSelectScene();
};


#endif  // TP_FINAL_CHARACTER_SELECT_H
