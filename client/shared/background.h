#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/common_constants.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/sprite.h"

#define BACKGROUNDS_FILE "assets/screens"
#define MAIN_MENU "main_menu"
#define MAIN_MENU_2 "main_menu_2"
#define MAIN_MENU_3 "main_menu_3"

class MainScreenBackground: public engine::CanvasObject {
private:
    SDL_Rect background_s_rect;
    SDL_Rect background_d_rect;
    std::unique_ptr<engine::Sprite> sprite;

public:
    explicit MainScreenBackground(const engine::ResourcePool& resource_pool);
    void draw(SDL_Renderer* renderer, int it) override;
    SDL_Rect& get_body() override;
};


#endif  // BACKGROUND_H
