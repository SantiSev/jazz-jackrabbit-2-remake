#ifndef EDITOR_HUD_H
#define EDITOR_HUD_H

#include <atomic>
#include <list>
#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../editor_objects/tile_manager.h"
#include "../event_loop.h"
#include "../menu_objects/save_exit_editor_button.h"

#include "tile.h"

class EditorHud: public engine::CanvasObject {
private:
    SDL_Rect body;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    TileManager& tile_manager;

    std::list<Tile> tiles;
    std::unique_ptr<SaveExitEditorButton> save_and_exit_button;

    void create_buttons(std::atomic<bool>& menu_running, std::atomic<bool>& editor_running);

public:
    EditorHud(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
              EventLoop* event_loop, TileManager& tile_manager, std::atomic<bool>& menu_running,
              std::atomic<bool>& editor_running);

    void draw(SDL_Renderer* renderer, int it) override;

    SDL_Rect& get_body() override;

    ~EditorHud() override;
};

#endif  // EDITOR_HUD_H
