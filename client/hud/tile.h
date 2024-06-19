#ifndef TILE_H
#define TILE_H

#include <memory>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/texture.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"

class TileManager;

class Tile: public engine::Sprite {
private:
    TileManager& tile_manager;

public:
    SDL_Rect src_rect;

    Tile(SDL_Rect& d_rect, SDL_Rect& s_rect, std::shared_ptr<engine::Texture> texture,
         TileManager& tile_manager);

    void on_click() override;

    ~Tile() override;
};

#endif  // TILE_H
