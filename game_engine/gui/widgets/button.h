#ifndef TP_FINAL_BUTTON_H
#define TP_FINAL_BUTTON_H

#include <SDL2/SDL.h>

#include "../../controllers/mouse.h"
#include "../canvas_object.h"

class Button: public CanvasObject {
private:
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    bool is_hovered;

public:
    explicit Button(SDL_Rect rect, SDL_Color color, SDL_Color hoverColor);

    void update(Mouse& mouse);
    void draw(SDL_Renderer* renderer) override;

    ~Button() override;
};


#endif  // TP_FINAL_BUTTON_H
