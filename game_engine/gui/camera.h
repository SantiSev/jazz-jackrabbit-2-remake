#ifndef CAMERA_H
#define CAMERA_H

#include <list>
#include <memory>
#include <mutex>

#include <SDL2/SDL.h>

#include "canvas_object.h"

namespace engine {
class Camera {
private:
    SDL_Rect screen;
    int lower_limit_x;
    int upper_limit_x;
    int lower_limit_y;
    int upper_limit_y;
    std::mutex mtx;

public:
    Camera(int w, int h, int lower_lim_x, int upper_lim_x, int lower_limit_y, int upper_limit_y);

    // Recenter the camera on the given body
    void recenter(const SDL_Rect& body);

    // Move the camera to the given position
    // if either pos is -1, the camera will not move in that direction
    void move_pos(int x, int y);

    // Adjust the object's position relative to the camera
    // returns true if the object is visible on the screen
    bool adjust_relative_position(CanvasObject& object);

    SDL_Rect& get_body();

    ~Camera();
};
}  // namespace engine

#endif  // CAMERA_H
