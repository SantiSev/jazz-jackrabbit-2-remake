#ifndef TP_FINAL_LABEL_H
#define TP_FINAL_LABEL_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../canvas_object.h"

class Label: public CanvasObject {
private:
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    std::string text;
    TTF_Font* font;
    bool is_hovered_m;

public:
    Label(const SDL_Rect& rect, const SDL_Color& color, const SDL_Color& hover_color,
          const std::string& text, TTF_Font* font);

    void draw(SDL_Renderer* renderer) override;

    void is_hovered(bool) override;

    void set_position(int x, int y) override;

    bool is_intersecting(SDL_Point&) override;
    bool is_intersecting(SDL_Rect&) override;

    ~Label() override;
};


#endif  // TP_FINAL_LABEL_H
