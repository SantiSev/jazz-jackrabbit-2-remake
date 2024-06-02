#ifndef TP_FINAL_COLOR_RECT_H
#define TP_FINAL_COLOR_RECT_H

#include "../canvas_object.h"
#include <SDL2/SDL.h>
#include "../../errors.h"

class ColorRect : public CanvasObject {
    private:
        SDL_Color color;
        SDL_Rect rect;

    public:
        ColorRect(const SDL_Color& color, SDL_Rect& rect);

        void draw(SDL_Renderer* renderer) override;

        void set_position(int x, int y) override;

        bool is_intersecting(SDL_Point& point) const override;
        bool is_intersecting(SDL_Rect& other) const override;

        ~ColorRect() override;
};

#endif //TP_FINAL_COLOR_RECT_H