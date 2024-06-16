#include "camera.h"

using engine::Camera;

Camera::Camera(int x, int y, int w, int h): screen({x, y, w, h}), map(nullptr) {}

void Camera::add_object(std::shared_ptr<CanvasObject> object) { objects.push_back(object); }

void Camera::remove_object(std::shared_ptr<CanvasObject> object) { objects.remove(object); }

void Camera::set_map(std::shared_ptr<Map> map) { this->map = map; }

void Camera::recenter(const SDL_Rect& body) {
    // calculate body center
    int body_center_x = body.x + body.w / 2;
    int body_center_y = body.y + body.h / 2;

    // center the camera on the body
    screen.x = body_center_x - screen.w / 2;
    if (screen.x < 0) {
        screen.x = 0;
    } else if (screen.x + screen.w > map->get_body().w) {
        screen.x = map->get_body().w - screen.w;
    }
    screen.y = body_center_y - screen.h / 2;
    if (screen.y < 0) {
        screen.y = 0;
    } else if (screen.y + screen.h > map->get_body().h) {
        screen.y = map->get_body().h - screen.h;
    }
}

void Camera::draw(SDL_Renderer* renderer, int it) {
    // draw the map
    if (map != nullptr) {
        map->draw_in_camera(renderer, screen, it);
    }

    for (auto& object: objects) {
        if (object->is_intersecting(screen)) {
            SDL_Rect& body = object->get_body();

            // calculate the object's position on the screen
            int x = body.x - screen.x;
            int y = body.y - screen.y;

            // draw the object
            object->set_position(x, y);
            object->draw(renderer, it);
        }
    }
}

SDL_Rect& Camera::get_body() { return screen; }

Camera::~Camera() = default;
