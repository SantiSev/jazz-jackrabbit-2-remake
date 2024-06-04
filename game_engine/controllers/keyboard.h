#ifndef TP_FINAL_KEYBOARD_H
#define TP_FINAL_KEYBOARD_H

#include <list>
#include <mutex>

#include <SDL2/SDL.h>

#include "../gui/canvas_object.h"

#include "controller.h"

namespace engine {
class Keyboard: public Controller {
private:
    std::list<CanvasObject*> signal_objs;
    bool is_special_key(const SDL_Keycode& key);
    std::mutex mtx;

public:
    Keyboard() = default;

    // cant copy
    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;

    void update(const SDL_Event& event) override;

    void add_on_key_down_signal_obj(CanvasObject* obj);
    void remove_on_key_down_signal_obj(CanvasObject* obj);

    ~Keyboard() override;
};
}  // namespace engine

#endif  // TP_FINAL_KEYBOARD_H
