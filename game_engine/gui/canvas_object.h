#ifndef TP_FINAL_CANVASOBJECT_H
#define TP_FINAL_CANVASOBJECT_H

#include <SDL2/SDL.h>

class CanvasObject {
public:
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update(int delta) {}

    virtual void on_click() {}
    virtual void is_hovered(bool) {}
    virtual void on_key_press(SDL_Keycode) {}

    virtual void set_position(int x, int y) = 0;

    virtual bool is_intersecting(SDL_Point&) = 0;
    virtual bool is_intersecting(SDL_Rect&) = 0;

    virtual ~CanvasObject() = default;
};


#endif  // TP_FINAL_CANVASOBJECT_H