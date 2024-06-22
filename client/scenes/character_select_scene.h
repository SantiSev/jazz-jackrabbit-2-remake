#ifndef TP_FINAL_CHARACTER_SELECT_H
#define TP_FINAL_CHARACTER_SELECT_H

#include <list>
#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
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
    std::unique_ptr<engine::CanvasObject> background;
    std::list<CharacterSelector> selectors;

    std::atomic<bool>& game_running;
    std::atomic<bool>& character_select_running;

    ClientMessageHandler& message_handler;

    void create_buttons();

public:
    character_t selected_character;

    CharacterSelectScene(engine::Window& window, EventLoop* event_loop,
                         std::shared_ptr<engine::ResourcePool> resource_pool,
                         std::atomic<bool>& game_running,
                         std::atomic<bool>& character_select_running,
                         ClientMessageHandler& message_handler);

    // cant copy
    CharacterSelectScene(const CharacterSelectScene&) = delete;
    CharacterSelectScene& operator=(const CharacterSelectScene&) = delete;

    void start();

    ~CharacterSelectScene();
};


#endif  // TP_FINAL_CHARACTER_SELECT_H
