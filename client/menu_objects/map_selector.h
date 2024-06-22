#ifndef MAP_SELECTOR_H
#define MAP_SELECTOR_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/sprite.h"

class MapSelector: public engine::CanvasObject {
private:
    uint16_t map_id;
    std::string map_name;

    // std::unique_ptr<engine::Sprite> character_text;

    uint16_t& selected_map_id;
    std::atomic<bool>& map_select_running;

    bool hovering;

public:
    MapSelector(std::shared_ptr<engine::ResourcePool> resource_pool, uint16_t map_id,
                      int x, int y, uint16_t& selected_map_id,
                      std::atomic<bool>& map_select_running);

    void draw(SDL_Renderer* renderer, int it) override;

    void on_click() override;
    void is_hovered(bool) override;

    SDL_Rect& get_body() override;

    bool is_intersecting(SDL_Point&) const override;

    ~MapSelector() override;
};

#endif
