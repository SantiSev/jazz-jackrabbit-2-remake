#include "event_loop.h"

EventLoop::EventLoop(std::atomic<bool>& game_running, std::atomic<bool>& menu_running):
        game_running(game_running), menu_running(menu_running), mouse(0, 0) {}

void EventLoop::run() {
    while (_keep_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                menu_running.store(false);
                game_running.store(false);
                break;
            }
            keyboard.update(event);
            mouse.update(event);
        }
        SDL_Delay(10);  // delay to avoid 100% CPU usage
    }
}

EventLoop::~EventLoop() = default;
