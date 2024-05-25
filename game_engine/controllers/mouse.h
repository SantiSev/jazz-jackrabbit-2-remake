#ifndef TP_FINAL_MOUSE_H
#define TP_FINAL_MOUSE_H

#include <list>

#include <SDL2/SDL.h>

typedef void (*on_click_signal_handler)(SDL_Point);

class Mouse {
private:
    std::list<on_click_signal_handler> signal_handlers;

public:
    SDL_Point cursor;
    explicit Mouse(int x, int y);
    void update(const SDL_Event& event);
    void add_on_click_signal_handler(on_click_signal_handler handler);
    void remove_on_click_signal_handler(on_click_signal_handler handler);
    ~Mouse();
};


#endif  // TP_FINAL_MOUSE_H
