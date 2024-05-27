#ifndef TP_FINAL_LABEL_H
#define TP_FINAL_LABEL_H

#include "../canvas_object.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Label : public CanvasObject {
private:
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    std::string text;
    TTF_Font* font;
    bool is_hovered_m;

public:
    Label(const SDL_Rect& rect,
          const SDL_Color& color,
          const SDL_Color& hover_color,
          const std::string& text,
          TTF_Font* font);

    void draw(SDL_Renderer* renderer) override;
    
    void is_hovered(bool) override;

    bool is_intersecting(SDL_Point&) override;
    bool is_intersecting(SDL_Rect&) override;

    ~Label() override;
};


#endif  // TP_FINAL_LABEL_H
