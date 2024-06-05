#ifndef TP_FINAL_CANVASOBJECT_H
#define TP_FINAL_CANVASOBJECT_H

#include <SDL2/SDL.h>

namespace engine {
class CanvasObject {
public:
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update(int delta) {}

    virtual void on_click() {}
    virtual void is_hovered(bool) {}
    virtual void on_key_press(const SDL_Keycode&) {}

    virtual void set_position(int x, int y) {};

    virtual bool is_intersecting(SDL_Point&) const { return false; };
    virtual bool is_intersecting(SDL_Rect&) const { return false; };

    virtual ~CanvasObject() = default;
};
}  // namespace engine

#endif  // TP_FINAL_CANVASOBJECT_H
