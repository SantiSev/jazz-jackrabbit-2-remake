#ifndef EDITOR_TILE_H
#define EDITOR_TILE_H

#include <atomic>
#include <memory>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/texture.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"

class TileManager;

class EditorTile: public engine::Sprite {
private:
    TileManager& tile_manager;
    SDL_Rect s_rect;
    SDL_Rect d_rect;

public:
    std::atomic<bool> visible;

    EditorTile(SDL_Rect& d_rect, SDL_Rect& s_rect, std::shared_ptr<engine::Texture> texture,
               TileManager& tile_manager);

    void on_click() override;

    SDL_Rect& get_d_rect();
    SDL_Rect& get_s_rect();

    ~EditorTile() override;
};

#endif  // EDITOR_TILE_H
