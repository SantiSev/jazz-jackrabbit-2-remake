#ifndef TP_FINAL_MAP_SELECT_H
#define TP_FINAL_MAP_SELECT_H

#include <atomic>
#include <list>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/color_rect.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../event_loop.h"
#include "../menu_objects/map_selector.h"
#include "../protocol/client_message_handler.h"
#include "../shared/background.h"


class MapSelectScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::unique_ptr<engine::CanvasObject> background;
    engine::Label title;
    engine::ColorRect title_background;
    std::list<MapSelector> selectors;

    std::atomic<bool>& game_running;
    std::atomic<bool>& map_select_running;
    std::atomic<bool>& character_select_running;

    ClientMessageHandler& message_handler;

    void create_buttons();

public:
    uint16_t selected_map_id;

    MapSelectScene(engine::Window& window, EventLoop* event_loop,
                   std::shared_ptr<engine::ResourcePool> resource_pool,
                   std::atomic<bool>& game_running, std::atomic<bool>& map_select_running,
                   std::atomic<bool>& character_select_running,
                   ClientMessageHandler& message_handler);

    // cant copy
    MapSelectScene(const MapSelectScene&) = delete;
    MapSelectScene& operator=(const MapSelectScene&) = delete;

    void start();

    ~MapSelectScene();
};


#endif  // TP_FINAL_MAP_SELECT_H
