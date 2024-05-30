#ifndef TP_FINAL_FONT_H
#define TP_FINAL_FONT_H

#include <string>

#include <SDL2/SDL_ttf.h>

#include "../../errors.h"

class Font {
private:
    TTF_Font* font;

public:
    explicit Font(const std::string& path, int size);

    TTF_Font* get_font() const;

    ~Font();
};


#endif  // TP_FINAL_FONT_H
