#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>

#include "../../common/assets.h"
#include "../../common/map_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../event_loop.h"
#include "../hud/tile.h"

#include "editor_tile.h"

class TileManager {
private:
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    SDL_Rect selected_tile;
    std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& tiles;

public:
    TileManager(std::shared_ptr<engine::ResourcePool> resource_pool, EventLoop* event_loop,
                std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& tiles_map);

    void set_selected_tile(const SDL_Rect& src_rect);
    SDL_Rect get_selected_tile();

    std::unordered_map<uint16_t, std::shared_ptr<EditorTile>>& get_tiles();

    ~TileManager();
};

#endif  // TILE_MANAGER_H
