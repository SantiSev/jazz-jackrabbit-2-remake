#include "button.h"

Button::Button(const SDL_Rect& rect, const SDL_Color& color, const SDL_Color& hover_color,
               Label& label):
        rect(rect), color(color), hover_color(hover_color), is_hovered_m(false), label(label) {}

void Button::on_click() {
    std::cout << "Button was clicked." << std::endl;
    label.on_click();
}

void Button::is_hovered(bool hovered) {
    is_hovered_m = hovered;
    label.is_hovered(hovered);
}

void Button::draw(SDL_Renderer* renderer) {
    if (is_hovered_m) {
        SDL_SetRenderDrawColor(renderer, hover_color.r, hover_color.g, hover_color.b,
                               hover_color.a);
    } else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderFillRect(renderer, &rect);

    label.draw(renderer);
}

bool Button::is_intersecting(SDL_Point& point) { return SDL_PointInRect(&point, &this->rect); }

bool Button::is_intersecting(SDL_Rect& other_rect) {
    return SDL_IntersectRect(&this->rect, &other_rect, NULL);
}

Button::~Button() = default;
