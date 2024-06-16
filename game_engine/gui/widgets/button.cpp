#include "button.h"

using engine::Button;

Button::Button(std::unique_ptr<Label> label, SDL_Rect& rect, const SDL_Color& color,
               const SDL_Color& hover_color):
        label(std::move(label)),
        rect(rect),
        color(color),
        hover_color(hover_color),
        is_hovered_m(false) {}

void Button::on_click() { label->on_click(); }

void Button::is_hovered(bool hovered) {
    is_hovered_m = hovered;
    label->is_hovered(hovered);
}

void Button::draw(SDL_Renderer* renderer, int it) {
    int err;
    if (is_hovered_m) {
        err = SDL_SetRenderDrawColor(renderer, hover_color.r, hover_color.g, hover_color.b,
                                     hover_color.a);
    } else {
        err = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    if (err < 0) {
        throw SDLError("Error setting color: " + std::string(SDL_GetError()));
    }

    err = SDL_RenderFillRect(renderer, &rect);
    if (err < 0) {
        throw SDLError("Error drawing button: " + std::string(SDL_GetError()));
    }

    label->draw(renderer, it);
}

SDL_Rect& Button::get_body() { return rect; }

void Button::set_position(int x, int y) {
    rect.x = x;
    rect.y = y;
    label->set_position(x, y);
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
