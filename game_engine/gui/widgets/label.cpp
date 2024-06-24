#include "label.h"

using engine::Label;

Label::Label(std::shared_ptr<Font> font, SDL_Rect rect, SDL_Color color, SDL_Color hover_color,
             const std::string& text, SDL_Renderer* renderer):
        font(font),
        rect(rect),
        color(color),
        hover_color(hover_color),
        texture(font, color, text, renderer),
        hover_texture(font, hover_color, text, renderer),
        text(text),
        is_hovered_m(false) {}

void Label::is_hovered(bool hovered) { is_hovered_m = hovered; }

void Label::draw(SDL_Renderer* renderer, int it) {
    int err = SDL_RenderCopy(renderer,
                             is_hovered_m ? hover_texture.get_texture() : texture.get_texture(),
                             nullptr, &rect);
    if (err < 0) {
        throw SDLError("Error drawing label: " + std::string(SDL_GetError()));
    }
}

void Label::center_x(int x, int w) {
    int new_center = x + w / 2;
    rect.x = new_center - rect.w / 2;
}

void Label::center_y(int y, int h) {
    int new_center = y + h / 2;
    rect.y = new_center - rect.h / 2;
}

void Label::center(int x, int y, int w, int h) {
    center_x(x, w);
    center_y(y, h);
}

SDL_Rect& Label::get_body() { return rect; }

void Label::set_position(int x, int y) {
    rect.x = x;
    rect.y = y;
}

std::string Label::get_text() { return text; }

void Label::set_text(const std::string& new_text, SDL_Renderer* renderer) {
    text = new_text;
    texture = Texture(font, color, text, renderer);
    hover_texture = Texture(font, hover_color, text, renderer);
}

bool Label::is_intersecting(SDL_Point& point) const {
    SDL_Rect point_rect = {point.x, point.y, 1, 1};
    return SDL_HasIntersection(&rect, &point_rect);
}

bool Label::is_intersecting(SDL_Rect& other_rect) const {
    return SDL_HasIntersection(&rect, &other_rect);
}

Label::Label(Label&& other) noexcept:
        font(std::move(other.font)),
        rect(other.rect),
        color(other.color),
        hover_color(other.hover_color),
        texture(std::move(other.texture)),
        hover_texture(std::move(other.hover_texture)),
        text(std::move(other.text)),
        is_hovered_m(other.is_hovered_m) {}

Label& Label::operator=(Label&& other) noexcept {
    if (this == &other)
        return *this;

    font = std::move(other.font);
    rect = other.rect;
    color = other.color;
    hover_color = other.hover_color;
    texture = std::move(other.texture);
    hover_texture = std::move(other.hover_texture);
    text = std::move(other.text);
    is_hovered_m = other.is_hovered_m;

    return *this;
}

Label::~Label() = default;
