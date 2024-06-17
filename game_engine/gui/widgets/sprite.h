#ifndef TP_FINAL_SPRITE_H
#define TP_FINAL_SPRITE_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../errors.h"
#include "../basic/texture.h"
#include "../canvas_object.h"

namespace engine {
class Sprite: public CanvasObject {
private:
    std::shared_ptr<Texture> texture;
    SDL_Rect s_rect;
    SDL_Rect d_rect;
    SDL_Rect body;

public:
    explicit Sprite(std::shared_ptr<Texture> texture, SDL_Rect& s_react, SDL_Rect& d_rect);

    // Cant copy
    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

    // Can move
    Sprite(Sprite&&) noexcept;
    Sprite& operator=(Sprite&&) noexcept;

    void draw(SDL_Renderer* renderer, int it) override;

    SDL_Rect& get_body() override;
    void set_position(int x, int y) override;

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~Sprite() override;
};
}  // namespace engine

#endif  // TP_FINAL_SPRITE_H
