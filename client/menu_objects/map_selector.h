#ifndef MAP_SELECTOR_H
#define MAP_SELECTOR_H

#include <atomic>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../../game_engine/gui/widgets/sprite.h"

class MapSelector: public engine::Button {
private:
    uint16_t map_id;
    uint16_t& selected_map_id;
    std::atomic<bool>& map_select_running;
    std::atomic<bool>& character_select_running;

    SDL_Color get_random_color();

public:
    MapSelector(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                const std::string& map_name, uint16_t map_id, int x, int y,
                uint16_t& selected_map_id, std::atomic<bool>& map_select_running,
                std::atomic<bool>& character_select_running);

    void on_click() override;

    ~MapSelector() override;
};

#endif
