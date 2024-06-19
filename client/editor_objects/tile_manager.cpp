#include "tile_manager.h"

TileManager::TileManager(std::shared_ptr<engine::ResourcePool> resource_pool, EventLoop* event_loop,
                         std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& tiles_map):
        event_loop(event_loop),
        resource_pool(resource_pool),
        selected_tile({0, 0, 0, 0}),
        tiles(tiles_map) {
    int map_width = 1280;
    int map_height = 640;
    int tile_width = 32;
    int tile_height = 32;
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

void TileManager::set_selected_tile(const SDL_Rect& src_rect) { selected_tile = src_rect; }

SDL_Rect TileManager::get_selected_tile() { return selected_tile; }

std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& TileManager::get_tiles() {
    return tiles;
}

TileManager::~TileManager() = default;
