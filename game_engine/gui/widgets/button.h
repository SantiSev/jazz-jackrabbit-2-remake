#ifndef TP_FINAL_BUTTON_H
#define TP_FINAL_BUTTON_H

#include <iostream>

#include <SDL2/SDL.h>

#include "../../controllers/mouse.h"
#include "../canvas_object.h"
#include "label.h"

class Button: public CanvasObject {
private:
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    bool is_hovered_m;
    Label label;

public:
    explicit Button(const SDL_Rect& rect,
                    const SDL_Color& color,
                    const SDL_Color& hoverColor,
                    Label& label);

    void draw(SDL_Renderer* renderer) override;

    void on_click() override;
    void is_hovered(bool) override;

    bool is_intersecting(SDL_Point&) override;
    bool is_intersecting(SDL_Rect&) override;

    ~Button() override;
};


#endif  // TP_FINAL_BUTTON_H
