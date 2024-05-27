#include "keyboard.h"

void Keyboard::update(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        for (auto obj: signal_objs) {
            obj->on_key_down(event.key.keysym.sym);
        }
    }
}

void Keyboard::add_on_key_down_signal_obj(CanvasObject* obj) { signal_objs.push_back(obj); }

void Keyboard::remove_on_key_down_signal_obj(CanvasObject* obj) { signal_objs.remove(obj); }

Keyboard::~Keyboard() = default;
