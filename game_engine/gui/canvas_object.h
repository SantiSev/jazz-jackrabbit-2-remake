#ifndef TP_FINAL_CANVASOBJECT_H
#define TP_FINAL_CANVASOBJECT_H

#include <SDL2/SDL.h>

class CanvasObject {
public:
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual ~CanvasObject() = default;
};


#endif  // TP_FINAL_CANVASOBJECT_H
