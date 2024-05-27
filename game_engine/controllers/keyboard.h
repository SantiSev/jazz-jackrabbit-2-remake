#ifndef TP_FINAL_KEYBOARD_H
#define TP_FINAL_KEYBOARD_H

#include <list>

#include <SDL2/SDL.h>

#include "../gui/canvas_object.h"

#include "controller.h"

class Keyboard: public Controller {
private:
    std::list<CanvasObject*> signal_objs;

public:
    void update(const SDL_Event& event) override;

    void add_on_key_down_signal_obj(CanvasObject* obj);
    void remove_on_key_down_signal_obj(CanvasObject* obj);

    ~Keyboard() override;
};


#endif  // TP_FINAL_KEYBOARD_H
