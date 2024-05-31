#ifndef TP_FINAL_MOUSE_H
#define TP_FINAL_MOUSE_H

#include <list>

#include <SDL2/SDL.h>

#include "../gui/canvas_object.h"

#include "controller.h"

class Mouse: public Controller {
private:
    std::list<CanvasObject*> signal_objs;

public:
    SDL_Point cursor;

    explicit Mouse(int x, int y);

    void update(const SDL_Event& event) override;

    void add_on_click_signal_obj(CanvasObject* obj);
    void remove_on_click_signal_obj(CanvasObject* obj);

    ~Mouse() override;
};


#endif  // TP_FINAL_MOUSE_H