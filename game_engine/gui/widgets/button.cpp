#include "button.h"

Button::Button(Label&& label, SDL_Rect& rect, const SDL_Color& color, const SDL_Color& hover_color):
        label(std::move(label)),
        rect(rect),
        color(color),
        hover_color(hover_color),
        is_hovered_m(false) {}

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

void Button::set_position(int x, int y) {
    rect.x = x;
    rect.y = y;
    label.set_position(x, y);
}

bool Button::is_intersecting(SDL_Point& point) const {
    return SDL_PointInRect(&point, &this->rect);
}

bool Button::is_intersecting(SDL_Rect& other_rect) const {
    return SDL_IntersectRect(&this->rect, &other_rect, NULL);
}

Button::Button(Button&& other) noexcept:
        label(std::move(other.label)),
        rect(other.rect),
        color(other.color),
        hover_color(other.hover_color),
        is_hovered_m(other.is_hovered_m) {}

Button& Button::operator=(Button&& other) noexcept {
    if (this == &other)
        return *this;

    label = std::move(other.label);
    rect = other.rect;
    color = other.color;
    hover_color = other.hover_color;
    is_hovered_m = other.is_hovered_m;

    return *this;
}

Button::~Button() = default;
