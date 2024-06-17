#include "color_rect.h"

using engine::ColorRect;

ColorRect::ColorRect(const SDL_Color& color, SDL_Rect& rect): color(color), rect(rect) {}

void ColorRect::draw(SDL_Renderer* renderer, int it) {
    int err = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (err < 0) {
        throw SDLError("Error setting color: " + std::string(SDL_GetError()));
    }

    err = SDL_RenderFillRect(renderer, &rect);

    if (err < 0) {
        throw SDLError("Error drawing color rect: " + std::string(SDL_GetError()));
    }
}

SDL_Rect& ColorRect::get_body() { return rect; }

void ColorRect::set_position(int x, int y) {
    rect.x = x;
    rect.y = y;
}

bool ColorRect::is_intersecting(SDL_Point& point) const { return SDL_PointInRect(&point, &rect); }

bool ColorRect::is_intersecting(SDL_Rect& other) const {
    return SDL_HasIntersection(&rect, &other);
}

ColorRect::~ColorRect() = default;
