#include "font.h"

Font::Font(const std::string& path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr) {
        throw FileDoesNotExist("Font file does not exist");
    }
}

TTF_Font* Font::get_font() const { return font; }

Font::~Font() { TTF_CloseFont(font); }
