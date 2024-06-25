#ifndef CHARACTER_ICON_H
#define CHARACTER_ICON_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"

const std::unordered_map<character_t, std::string> map_character_enum_to_icon_name = {
        {JAZZ_CHARACTER, "jazz"}, {SPAZ_CHARACTER, "spaz"}, {LORI_CHARACTER, "lori"}};

class CharacterIcon: public engine::CanvasObject {
private:
    std::unique_ptr<engine::Sprite> icon;

public:
    CharacterIcon(std::shared_ptr<engine::ResourcePool> resource_pool, int x, int y,
                  character_t character_type);

    void draw(SDL_Renderer* renderer, int it) override;

    SDL_Rect& get_body() override;

    ~CharacterIcon() override;
};

#endif  // CHARACTER_ICON_H
