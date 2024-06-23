#ifndef CHARACTER_SELECTOR_H
#define CHARACTER_SELECTOR_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/sprite.h"

#define CHARACTER_SELECT_BACKGROUND "character_select_background"
#define RIPPED_CHARACTER_APPEND "-ripped"
#define CHARACTER_TEXT_APPEND "-text"

const std::unordered_map<character_t, std::string> map_character_to_selector = {
        {JAZZ_CHARACTER, "jazz"}, {SPAZ_CHARACTER, "spaz"}, {LORI_CHARACTER, "lori"}};

class CharacterSelector: public engine::CanvasObject {
private:
    character_t character;
    std::string character_name;
    std::string ripped_character_name;
    std::string character_text_name;

    std::unique_ptr<engine::Sprite> character_text;
    std::unique_ptr<engine::Sprite> character_sprite;
    std::unique_ptr<engine::Sprite> ripped_character_sprite;

    character_t& selected_character;
    std::atomic<bool>& character_select_running;

    bool hovering;

public:
    CharacterSelector(std::shared_ptr<engine::ResourcePool> resource_pool, character_t character,
                      int x, int y, character_t& selected_character,
                      std::atomic<bool>& character_select_running);

    void draw(SDL_Renderer* renderer, int it) override;

    void on_click() override;
    void is_hovered(bool) override;

    SDL_Rect& get_body() override;

    bool is_intersecting(SDL_Point&) const override;

    ~CharacterSelector() override;
};

#endif
