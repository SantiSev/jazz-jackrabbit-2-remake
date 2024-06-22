#include "tile_selector.h"

#include "tile_manager.h"

TileSelector::TileSelector(SDL_Rect& d_rect, SDL_Rect& s_rect,
                           std::shared_ptr<engine::Texture> texture, TileManager& tile_manager,
                           TileType type):
        engine::Sprite(texture, s_rect, d_rect),
        tile_manager(tile_manager),
        type(type),
        src_rect(s_rect) {}

void TileSelector::on_click() {
#ifdef LOG
    std::cout << "Clicked Selection Tile." << std::endl;
#endif
    tile_manager.set_selected_tile(src_rect, type);
}

TileSelector::~TileSelector() = default;
