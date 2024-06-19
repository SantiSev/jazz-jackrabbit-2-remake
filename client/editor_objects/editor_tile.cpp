#include "editor_tile.h"

#include "../editor_objects/tile_manager.h"

EditorTile::EditorTile(SDL_Rect& d_rect, SDL_Rect& s_rect, std::shared_ptr<engine::Texture> texture,
                       TileManager& tile_manager):
        engine::Sprite(texture, s_rect, d_rect), tile_manager(tile_manager) {}

void EditorTile::on_click() {
#ifdef LOG
    std::cout << "Clicked editor tile." << std::endl;
#endif
    this->change_source(tile_manager.get_selected_tile());
}

EditorTile::~EditorTile() = default;
