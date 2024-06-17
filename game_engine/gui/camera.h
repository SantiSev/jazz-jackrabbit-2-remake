#ifndef CAMERA_H
#define CAMERA_H

#include <list>
#include <memory>

#include <SDL2/SDL.h>

#include "canvas_object.h"

namespace engine {
class Camera {
private:
    SDL_Rect screen;
    int limit_x;
    int limit_y;

public:
    Camera(int w, int h, int limit_x, int limit_y);

    // Recenter the camera on the given body
    void recenter(const SDL_Rect& body);

    // Adjust the object's position relative to the camera
    // returns true if the object is visible on the screen
    bool adjust_relative_position(CanvasObject& object);

    SDL_Rect& get_body();

    ~Camera();
};
}  // namespace engine

#endif  // CAMERA_H
