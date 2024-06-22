#include "map_selector.h"

MapSelector::MapSelector(std::shared_ptr<engine::ResourcePool> resource_pool,
                                     uint16_t map_id, int x, int y,
                                     uint16_t& selected_map_id,
                                     std::atomic<bool>& map_select_running):
        map_id(map_id),
        // map_name(),
        selected_map_id(selected_map_id),
        map_select_running(map_select_running),
        hovering(false) {
    auto texture = resource_pool->get_texture(CHARACTER_SELECT_FILE);
    auto yaml = *resource_pool->get_yaml(CHARACTER_SELECT_FILE);
}

void MapSelector::draw(SDL_Renderer* renderer, int it) {
    //
}

void MapSelector::on_click() {
    selected_map_id = map_id;
    map_select_running.store(false);
}

void MapSelector::is_hovered(bool hovering_p) { hovering = hovering_p; }

SDL_Rect& MapSelector::get_body() { 
    // return character_sprite->get_body();
}

bool MapSelector::is_intersecting(SDL_Point& point) const {
    // return character_sprite->is_intersecting(point);
}

MapSelector::~MapSelector() = default;
