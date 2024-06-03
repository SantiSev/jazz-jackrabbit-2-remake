#include "keyboard.h"

using engine::Keyboard;

void Keyboard::update(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        for (auto obj: signal_objs) {
            obj->on_key_press(event.key.keysym.sym);
        }
    } else if (event.type == SDL_KEYUP) {
        if (!is_special_key(event.key.keysym.sym))
            return;
        for (auto obj: signal_objs) {
            obj->on_key_press(event.key.keysym.sym);
        }
    }
}

void Keyboard::add_on_key_down_signal_obj(CanvasObject* obj) { signal_objs.push_back(obj); }

void Keyboard::remove_on_key_down_signal_obj(CanvasObject* obj) { signal_objs.remove(obj); }

bool Keyboard::is_special_key(const SDL_Keycode& key) { return key == SDLK_LSHIFT; }

Keyboard::~Keyboard() = default;
