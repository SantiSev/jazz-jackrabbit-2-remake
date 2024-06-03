#ifndef TP_FINAL_COLOR_RECT_H
#define TP_FINAL_COLOR_RECT_H

#include <string>

#include <SDL2/SDL.h>

#include "../../errors.h"
#include "../canvas_object.h"

namespace engine {
class ColorRect: public CanvasObject {
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
}  // namespace engine

#endif  // TP_FINAL_COLOR_RECT_H
