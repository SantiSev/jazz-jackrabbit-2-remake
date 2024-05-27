#include "mouse.h"

Mouse::Mouse(int x, int y): cursor({x, y}) {}

void Mouse::update(const SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&cursor.x, &cursor.y);
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState(&cursor.x, &cursor.y);
        for (auto obj: signal_objs) {
            if (obj->is_intersecting(this->cursor)) {
                obj->on_click();
            }
        }
    }
}

void Mouse::add_on_click_signal_obj(CanvasObject* obj) { signal_objs.push_back(obj); }

void Mouse::remove_on_click_signal_obj(CanvasObject* obj) { signal_objs.remove(obj); }

Mouse::~Mouse() = default;
