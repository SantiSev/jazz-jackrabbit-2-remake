#include "event_loop.h"

EventLoop::EventLoop(std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     std::atomic<bool>& match_running, ClientMessageHandler& message_handler):
        game_running(game_running),
        menu_running(menu_running),
        match_running(match_running),
        message_handler(message_handler),
        mouse(0, 0),
        recv_message() {}

void EventLoop::run() {
    while (_keep_running) {
        while (SDL_PollEvent(&event)) {
            std::shared_ptr<Message> msg;
            recv_message.try_pop(msg);
            if (msg) {
                msg->run(message_handler);
            }
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
        SDL_Delay(10);  // delay to avoid 100% CPU usage
    }
}

EventLoop::~EventLoop() = default;
