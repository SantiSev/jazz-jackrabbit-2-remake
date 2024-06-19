#include "camera.h"

using engine::Camera;
using engine::CanvasObject;

Camera::Camera(int w, int h, int lower_lim_x, int upper_lim_x, int lower_limit_y,
               int upper_limit_y):
        screen({lower_lim_x, lower_limit_y, w, h}),
        lower_limit_x(lower_lim_x),
        upper_limit_x(upper_lim_x),
        lower_limit_y(lower_limit_y),
        upper_limit_y(upper_limit_y) {}

void Camera::recenter(const SDL_Rect& body) {
    // calculate body center
    int body_center_x = body.x + (body.w / 2);
    int body_center_y = body.y + (body.h / 2);

    // center the camera on the body
    move_pos(body_center_x - screen.w / 2, body_center_y - screen.h / 2);
}

void Camera::move_pos(int x, int y) {
    std::unique_lock<std::mutex> lock(mtx);
    if (x != -1) {
        screen.x = x;
        if (screen.x < 0) {
            screen.x = 0;
        } else if (screen.x + screen.w > upper_limit_x) {
            screen.x = upper_limit_x - screen.w;
        } else if (screen.x < lower_limit_x) {
            screen.x = lower_limit_x;
        }
    }
    if (y != -1) {
        screen.y = y;
        if (screen.y < 0) {
            screen.y = 0;
        } else if (screen.y + screen.h > upper_limit_y) {
            screen.y = upper_limit_y - screen.h;
        } else if (screen.y < lower_limit_y) {
            screen.y = lower_limit_y;
        }
    }
}

bool Camera::adjust_relative_position(CanvasObject& object) {
    std::unique_lock<std::mutex> lock(mtx);
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
