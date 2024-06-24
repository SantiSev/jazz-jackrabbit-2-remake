#ifndef INGAME_HUD_H
#define INGAME_HUD_H

#include <atomic>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/color_rect.h"
#include "../editor_objects/save_exit_editor_button.h"
#include "../editor_objects/tile_enum.h"
#include "../editor_objects/tile_manager.h"
#include "../editor_objects/tile_selector.h"
#include "../event_loop.h"
#include "../icons/bullet_icon.h"
#include "../icons/character_icon.h"
#include "../icons/health_bar_icon.h"

class IngameHud: public engine::CanvasObject {
private:
    SDL_Rect body;
    SDL_Renderer* renderer;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    std::unique_ptr<engine::Label> timer;
    std::unique_ptr<engine::Label> username;
    std::unique_ptr<engine::Label> score;

    std::unique_ptr<CharacterIcon> character_icon;
    std::unique_ptr<HealthBarIcon> health;
    std::list<BulletIcon> bullets;
    bullet_type_t selected_weapon;

    void create_objects(const PlayerDTO& player_info, uint16_t seconds_left);

public:
    IngameHud(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
              const PlayerDTO& player_info, uint16_t seconds_left);

    void update(const PlayerDTO& player_info, uint16_t seconds_left);
    void draw(SDL_Renderer* renderer, int it) override;

    SDL_Rect& get_body() override;

    ~IngameHud() override;
};

#endif  // INGAME_HUD_H
