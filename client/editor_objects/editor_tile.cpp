#include "editor_tile.h"

#include "../editor_objects/tile_manager.h"

EditorTile::EditorTile(SDL_Rect& d_rect, SDL_Rect& s_rect, std::shared_ptr<engine::Texture> texture,
                       TileManager& tile_manager):
        engine::Sprite(texture, s_rect, d_rect),
        tile_manager(tile_manager),
        s_rect(s_rect),
        d_rect(d_rect),
        type(NULL_TILE),
        visible(false) {}

void EditorTile::on_click() {
    if (!visible)
        return;
#ifdef LOG
    std::cout << "Clicked editor tile." << std::endl;
#endif
    auto [rect, tile_type] = tile_manager.get_selected_tile();
    this->change_source(rect);
    type = tile_type;
    s_rect = rect;
}

SDL_Rect& EditorTile::get_d_rect() { return d_rect; }

SDL_Rect& EditorTile::get_s_rect() { return s_rect; }

EditorTile::~EditorTile() = default;
