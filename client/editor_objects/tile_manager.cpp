#include "tile_manager.h"

TileManager::TileManager(std::shared_ptr<engine::ResourcePool> resource_pool, EventLoop* event_loop,
                         std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& tiles_map):
        event_loop(event_loop),
        resource_pool(resource_pool),
        selected_tile({0, 0, TILE_SIZE, TILE_SIZE}),  // null tile by default
        selected_tile_type(TileType::NULL_TILE),
        tiles(tiles_map) {
    int map_width = resource_pool->get_config()->map_ed_max_width;
    int map_height = resource_pool->get_config()->map_ed_max_height;
    int tile_width = TILE_SIZE;
    int tile_height = TILE_SIZE;
    int num_tiles_per_row = map_width / tile_width;
    int num_tiles_per_col = map_height / tile_height;

    auto texture = resource_pool->get_texture(EDITOR_FILE);
    SDL_Rect src_rect = {0, 0, tile_width, tile_height};

    for (int i = 0; i < num_tiles_per_row; i++) {
        for (int j = 0; j < num_tiles_per_col; j++) {
            SDL_Rect dest_rect = {i * tile_width, j * tile_height, tile_width, tile_height};
            uint16_t tile_id = i + j * num_tiles_per_row;
            auto sprite = std::make_shared<EditorTile>(dest_rect, src_rect, texture, *this);
            event_loop->mouse.add_on_click_signal_obj(sprite.get());
            tiles.insert({tile_id, sprite});
        }
    }
}

void TileManager::set_selected_tile(const SDL_Rect& src_rect, const TileType& type) {
    selected_tile = src_rect;
    selected_tile_type = type;
}

std::pair<SDL_Rect, TileType> TileManager::get_selected_tile() {
    return {selected_tile, selected_tile_type};
}

std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& TileManager::get_tiles() {
    return tiles;
}

TileManager::~TileManager() = default;
