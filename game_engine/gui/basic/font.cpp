#include "font.h"

Font::Font(const std::string& path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr) {
        throw FileDoesNotExist("Font file does not exist");
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
