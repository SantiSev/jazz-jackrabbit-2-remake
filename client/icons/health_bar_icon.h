#ifndef HEALTH_BAR_ICON_H
#define HEALTH_BAR_ICON_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/sprite.h"

#define MAX_HEARTS 10

class HealthBarIcon: public engine::CanvasObject {
private:
    int max_health;
    int health_per_hearts;
    int bright_hearts;

    SDL_Rect src_bright_hearts;
    SDL_Rect src_dark_hearts;

    std::vector<engine::Sprite> hearts;

public:
    HealthBarIcon(std::shared_ptr<engine::ResourcePool> resource_pool, int x, int y, int health);

    void draw(SDL_Renderer* renderer, int it) override;
    void update_health(int new_health);

    SDL_Rect& get_body() override;

    ~HealthBarIcon() override;
};

#endif
