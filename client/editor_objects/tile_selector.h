#ifndef TILE_H
#define TILE_H

#include <memory>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/texture.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../editor_objects/tile_enum.h"

class TileManager;

class TileSelector: public engine::Sprite {
private:
    TileManager& tile_manager;

public:
    TileType type;
    SDL_Rect src_rect;

    TileSelector(SDL_Rect& d_rect, SDL_Rect& s_rect, std::shared_ptr<engine::Texture> texture,
                 TileManager& tile_manager, TileType type);

    void on_click() override;

    ~TileSelector() override;
};

#endif  // TILE_H
