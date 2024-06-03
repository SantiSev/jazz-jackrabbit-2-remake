#ifndef TP_FINAL_FONT_H
#define TP_FINAL_FONT_H

#include <string>

#include <SDL2/SDL_ttf.h>

#include "../../errors.h"

namespace engine {
class Font {
private:
    TTF_Font* font;

public:
    explicit Font(const std::string& path, int size);

    // Cant copy
    Font(const Font& other) = delete;
    Font& operator=(const Font& other) = delete;

    // Move constructors
    Font(Font&& other) noexcept;
    Font& operator=(Font&& other) noexcept;

    TTF_Font* get_font() const;

    ~Font();
};
}  // namespace engine

#endif  // TP_FINAL_FONT_H
