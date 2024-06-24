#ifndef BULLET_ICON_H
#define BULLET_ICON_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/sfx_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../../game_engine/gui/widgets/sprite.h"

class BulletIcon: public engine::CanvasObject {
private:
    std::unique_ptr<engine::Sprite> icon;
    std::unique_ptr<engine::Label> amount_label;

public:
    BulletIcon(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool, int x,
               int y, int amount, bullet_type_t bullet_type);

    void draw(SDL_Renderer* renderer, int it) override;
    void update_amount(int new_amount, SDL_Renderer* renderer);

    SDL_Rect& get_body() override;

    ~BulletIcon() override;
};

#endif  // BULLET_ICON_H
