#ifndef TP_FINAL_CONTROLLER_H
#define TP_FINAL_CONTROLLER_H

#include <SDL2/SDL.h>

class Controller {
public:
    virtual void update(const SDL_Event& event) = 0;
    virtual ~Controller() = default;
};


#endif  // TP_FINAL_CONTROLLER_H
