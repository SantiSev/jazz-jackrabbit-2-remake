#include "sprite.h"

Sprite::Sprite(const std::shared_ptr<SDL_Texture*>& texture, SDL_Rect& s_rect, SDL_Rect& d_rect):
        texture(texture), s_rect(s_rect), d_rect(d_rect) {}

void Sprite::draw(SDL_Renderer* renderer) { SDL_RenderCopy(renderer, *texture, &s_rect, &d_rect); }

void Sprite::set_position(int x, int y) {
    d_rect.x = x;
    d_rect.y = y;
}

bool Sprite::is_intersecting(SDL_Point& point) { return SDL_PointInRect(&point, &d_rect); }

bool Sprite::is_intersecting(SDL_Rect& rect) { return SDL_HasIntersection(&d_rect, &rect); }

Sprite::~Sprite() = default;
