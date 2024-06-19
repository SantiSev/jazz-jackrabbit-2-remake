#include "camera.h"

using engine::Camera;
using engine::CanvasObject;

Camera::Camera(int w, int h, int limit_x, int limit_y):
        screen({0, 0, w, h}), limit_x(limit_x), limit_y(limit_y) {}

void Camera::recenter(const SDL_Rect& body) {
    // calculate body center
    int body_center_x = body.x + body.w / 2;
    int body_center_y = body.y + body.h / 2;

    // center the camera on the body
    screen.x = body_center_x - screen.w / 2;
    if (screen.x < 0) {
        screen.x = 0;
    } else if (screen.x + screen.w > limit_x) {
        screen.x = limit_x - screen.w;
    }
    screen.y = body_center_y - screen.h / 2;
    if (screen.y < 0) {
        screen.y = 0;
    } else if (screen.y + screen.h > limit_y) {
        screen.y = limit_y - screen.h;
    }
}

bool Camera::adjust_relative_position(CanvasObject& object) {
    if (object.is_intersecting(screen)) {
        SDL_Rect& body = object.get_body();

        // calculate the object's position on the screen
        int x = body.x - screen.x;
        int y = body.y - screen.y;
        object.set_position(x, y);
        return true;
    }
    return false;
}

SDL_Rect& Camera::get_body() { return screen; }

Camera::~Camera() = default;
