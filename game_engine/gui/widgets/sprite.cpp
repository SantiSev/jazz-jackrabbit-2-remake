#include "sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Rect& s_rect, SDL_Rect& d_rect):
        texture(texture), s_rect(s_rect), d_rect(d_rect) {}

void Sprite::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture->get_texture(), &s_rect, &d_rect);
}

void Sprite::set_position(int x, int y) {
    d_rect.x = x;
    d_rect.y = y;
}

bool Sprite::is_intersecting(SDL_Point& point) const { return SDL_PointInRect(&point, &d_rect); }

bool Sprite::is_intersecting(SDL_Rect& rect) const { return SDL_HasIntersection(&d_rect, &rect); }

Sprite::Sprite(Sprite&& other) noexcept:
        texture(std::move(other.texture)), s_rect(other.s_rect), d_rect(other.d_rect) {}

Sprite& Sprite::operator=(Sprite&& other) noexcept {
    if (this == &other)
        return *this;

    texture = std::move(other.texture);
    s_rect = other.s_rect;
    d_rect = other.d_rect;

    return *this;
}

Sprite::~Sprite() = default;
