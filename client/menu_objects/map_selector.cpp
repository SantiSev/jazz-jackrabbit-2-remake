#include "map_selector.h"

MapSelector::MapSelector(SDL_Renderer* renderer,
                         std::shared_ptr<engine::ResourcePool> resource_pool,
                         const std::string& map_name, uint16_t map_id, int x, int y,
                         uint16_t& selected_map_id, std::atomic<bool>& map_select_running,
                         std::atomic<bool>& character_select_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), {x, y, 50, 20}, {255, 255, 255, 255},
                               {0, 0, 0, 255}, map_name, renderer)),
                       {x, y, 100, 30}, get_random_color(), get_random_color()),
        map_id(map_id),
        selected_map_id(selected_map_id),
        map_select_running(map_select_running),
        character_select_running(character_select_running) {}

void MapSelector::on_click() {
    selected_map_id = map_id;
    map_select_running.store(false);
    character_select_running.store(true);
}

SDL_Color MapSelector::get_random_color() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Uint8 r = rand() % 256;
    Uint8 g = rand() % 256;
    Uint8 b = rand() % 256;
    return SDL_Color{r, g, b, 255};
}

MapSelector::~MapSelector() = default;
