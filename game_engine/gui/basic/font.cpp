#include "font.h"

using engine::Font;

Font::Font(const std::string& file, int size) {
    font = TTF_OpenFont(file.c_str(), size);
    if (font == nullptr) {
        throw SDLError("Error opening font: " + std::string(TTF_GetError()));
    }
}

TTF_Font* Font::get_font() const { return font; }

Font::Font(Font&& other) noexcept: font(other.font) { other.font = nullptr; }

Font& Font::operator=(Font&& other) noexcept {
    if (this == &other)
        return *this;

    font = other.font;
    other.font = nullptr;

    return *this;
}

Font::~Font() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}
