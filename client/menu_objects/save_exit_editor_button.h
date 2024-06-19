#ifndef SAVE_EXIT_BUTTON_H
#define SAVE_EXIT_BUTTON_H

#include <atomic>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../editor_objects/tile_manager.h"
#include "../protocol/client_message_handler.h"

class SaveExitEditorButton: public engine::Button {
private:
    std::atomic<bool>& menu_running;
    std::atomic<bool>& editor_running;
    TileManager& tile_manager;

    void save_map();

public:
    SaveExitEditorButton(SDL_Renderer* renderer,
                         std::shared_ptr<engine::ResourcePool> resource_pool, SDL_Rect& d_rect,
                         std::atomic<bool>& menu_running, std::atomic<bool>& editor_running,
                         TileManager& tile_manager);

    void on_click() override;

    ~SaveExitEditorButton() override;
};

#endif  // SAVE_EXIT_BUTTON_H
