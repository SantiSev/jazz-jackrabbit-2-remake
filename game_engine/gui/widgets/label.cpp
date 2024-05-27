#include "label.h"

Label::Label(const SDL_Rect& rect, const SDL_Color& color, const SDL_Color& hover_color,
             const std::string& text, TTF_Font* font):
        rect(rect),
        color(color),
        hover_color(hover_color),
        text(text),
        font(font),
        is_hovered_m(false) {}

void Label::is_hovered(bool hovered) { is_hovered_m = hovered; }

void Label::draw(SDL_Renderer* renderer) {
    SDL_Surface* surface =
            TTF_RenderText_Solid(font, text.c_str(), is_hovered_m ? hover_color : color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect text_rect = {rect.x, rect.y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool Label::is_intersecting(SDL_Point& point) {
    SDL_Rect point_rect = {point.x, point.y, 1, 1};
    return SDL_HasIntersection(&rect, &point_rect);
}

bool Label::is_intersecting(SDL_Rect& other_rect) {
    return SDL_HasIntersection(&rect, &other_rect);
}

Label::~Label() = default;
