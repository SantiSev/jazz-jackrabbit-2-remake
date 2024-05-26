#include "button.h"

Button::Button(SDL_Rect rect, SDL_Color color, SDL_Color hover_color):
        rect(rect), color(color), hover_color(hover_color), is_hovered(false) {}

void Button::update(Mouse& mouse) {
    SDL_Point mousePoint = {mouse.cursor.x, mouse.cursor.y};
    is_hovered = SDL_PointInRect(&mousePoint, &this->rect);
}

void Button::on_click() { std::cout << "I was clicked" << std::endl; }

void Button::draw(SDL_Renderer* renderer) {
    if (is_hovered) {
        SDL_SetRenderDrawColor(renderer, hover_color.r, hover_color.g, hover_color.b,
                               hover_color.a);
    } else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderFillRect(renderer, &rect);
}

bool Button::is_intersecting(SDL_Point& point) { return SDL_PointInRect(&point, &this->rect); }

bool Button::is_intersecting(SDL_Rect& other_rect) {
    return SDL_IntersectRect(&this->rect, &other_rect, NULL);
}

Button::~Button() = default;
