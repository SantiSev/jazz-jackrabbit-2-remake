#include "sprite.h"

Sprite::Sprite(const std::string& file, const SDL_Rect& s_rect, const SDL_Rect& d_rect):
        s_rect(s_rect), d_rect(d_rect) {
    surface = IMG_Load(file.c_str());
    if (surface == nullptr) {
        throw std::runtime_error("Error loading image");
    }
}

void Sprite::draw(SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, &s_rect, &d_rect);
    SDL_DestroyTexture(texture);
}

void Sprite::set_position(int x, int y) {
    d_rect.x = x;
    d_rect.y = y;
}

bool Sprite::is_intersecting(SDL_Point& point) { return SDL_PointInRect(&point, &d_rect); }

bool Sprite::is_intersecting(SDL_Rect& rect) { return SDL_HasIntersection(&d_rect, &rect); }

Sprite::~Sprite() { SDL_FreeSurface(surface); }
