#ifndef TP_FINAL_EVENT_LOOP_H
#define TP_FINAL_EVENT_LOOP_H

#include <SDL2/SDL.h>

#include "../common/common_thread.h"
#include "../game_engine/controllers/keyboard.h"
#include "../game_engine/controllers/mouse.h"

class EventLoop: public Thread {
private:
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;
    SDL_Event event;

public:
    engine::Keyboard keyboard;
    engine::Mouse mouse;

    explicit EventLoop(std::atomic<bool>& game_running, std::atomic<bool>& menu_running);

    void run() override;

    ~EventLoop() override;
};


#endif
