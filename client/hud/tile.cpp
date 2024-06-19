#include "tile.h"

#include "../editor_objects/tile_manager.h"

Tile::Tile(SDL_Rect& d_rect, SDL_Rect& s_rect, std::shared_ptr<engine::Texture> texture,
           TileManager& tile_manager):
        engine::Sprite(texture, s_rect, d_rect), tile_manager(tile_manager), src_rect(s_rect) {}

void Tile::on_click() {
#ifdef LOG
    std::cout << "Clicked Selection Tile." << std::endl;
#endif
    tile_manager.set_selected_tile(src_rect);
}

Tile::~Tile() = default;
