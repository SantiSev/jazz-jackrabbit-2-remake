#include "ingame_hud.h"

IngameHud::IngameHud(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                     const PlayerDTO& player_info, uint16_t seconds_left):
        body({0, 0, 0, 0}),
        renderer(renderer),
        resource_pool(std::move(resource_pool)),
        timer(nullptr),
        username(nullptr),
        score(nullptr),
        character_icon(nullptr),
        health(nullptr) {
#ifdef LOG
    std::cout << "Constructing IngameHud..." << std::endl;
#endif
    create_objects(player_info, seconds_left);
}

void IngameHud::create_objects(const PlayerDTO& player_info, uint16_t seconds_left) {
    auto font = resource_pool->get_font(FONT);
    SDL_Rect timer_rect = {400 - 65, 40, 80, 50};
    timer = std::make_unique<engine::Label>(font, timer_rect, SDL_Color{255, 255, 255, 255},
                                            SDL_Color{255, 255, 255, 255},
                                            std::to_string(seconds_left), renderer);

    SDL_Rect username_rect = {75, 30, 60, 15};
    username = std::make_unique<engine::Label>(font, username_rect, SDL_Color{0, 0, 0, 255},
                                               SDL_Color{0, 0, 0, 255},
                                               std::string(player_info.name), renderer);

    SDL_Rect score_rect = {75, 50, 50, 15};
    score = std::make_unique<engine::Label>(
            font, score_rect, SDL_Color{0, 0, 0, 255}, SDL_Color{0, 0, 0, 255},
            "Score: " + std::to_string(player_info.points), renderer);

    character_icon = std::make_unique<CharacterIcon>(
            resource_pool, 10, 10, static_cast<character_t>(player_info.character));

    health = std::make_unique<HealthBarIcon>(resource_pool, 10, 80, player_info.health);

    for (int i = 0; i < 4; i++) {
        bullets.emplace_back(renderer, resource_pool, 10, 110, player_info.weapons[i].ammo,
                             static_cast<bullet_type_t>(player_info.weapons[i].weapon_name));
    }

    selected_weapon = static_cast<bullet_type_t>(player_info.selected_weapon);
}

void IngameHud::update(const PlayerDTO& player_info, uint16_t seconds_left) {
    timer->set_text(std::to_string(seconds_left), renderer);
    score->set_text("Score: " + std::to_string(player_info.points), renderer);
    health->update_health(player_info.health);
    int i = 0;
    for (auto& bullet: bullets) {
        bullet.update_amount(player_info.weapons[i].ammo, renderer);
        i++;
    }
    selected_weapon = static_cast<bullet_type_t>(player_info.selected_weapon);
}

void IngameHud::draw(SDL_Renderer* renderer, int it) {
    timer->draw(renderer, it);
    character_icon->draw(renderer, it);
    username->draw(renderer, it);
    score->draw(renderer, it);
    health->draw(renderer, it);
    auto bullet = std::find_if(bullets.begin(), bullets.end(), [this](const BulletIcon& bullet) {
        return bullet.type == selected_weapon;
    });
    if (bullet != bullets.end()) {
        bullet->draw(renderer, it);
    }
}

SDL_Rect& IngameHud::get_body() { return body; }

IngameHud::~IngameHud() = default;
