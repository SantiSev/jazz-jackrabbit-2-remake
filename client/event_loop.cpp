#include "event_loop.h"

EventLoop::EventLoop(std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     std::atomic<bool>& match_running, ClientMessageHandler& message_handler):
        game_running(game_running),
        menu_running(menu_running),
        match_running(match_running),
        message_handler(message_handler),
        mouse(0, 0) {}

void EventLoop::run() {
    const Uint32 rate = 1000 / 60;

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;

    while (_keep_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                message_handler.quit();
                menu_running.store(false);
                game_running.store(false);
                match_running.store(false);
                break;
            }
            keyboard.update(event);
            mouse.update(event);
        }

        frame_end = SDL_GetTicks();
        int rest_time = rate - (frame_end - frame_start);

        if (rest_time < 0) {
            behind = -rest_time;
            rest_time = rate - (behind % rate);
            lost = behind / rate;
            frame_start += lost;
        }

        SDL_Delay(rest_time);
        frame_start += rate;
    }
}

EventLoop::~EventLoop() = default;
