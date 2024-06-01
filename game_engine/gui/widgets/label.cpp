#include "label.h"

Label::Label(std::shared_ptr<Font> font, SDL_Rect& rect, const SDL_Color& color,
             const SDL_Color& hover_color, const std::string& text, SDL_Renderer* renderer):
        font(font),
        rect(rect),
        color(color),
        hover_color(hover_color),
        texture(font, color, text, renderer),
        hover_texture(font, hover_color, text, renderer),
        text(text),
        is_hovered_m(false) {}

void Label::is_hovered(bool hovered) { is_hovered_m = hovered; }

void Label::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, is_hovered_m ? hover_texture.get_texture() : texture.get_texture(),
                   nullptr, &rect);
}

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
