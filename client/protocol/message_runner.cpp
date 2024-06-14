#include "message_runner.h"

MessageRunner::MessageRunner(ClientMessageHandler& message_handler):
        message_handler(message_handler) {}

void MessageRunner::run() {
    const Uint32 rate = 1000 / 60;

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    int rest_time;
    Uint32 behind;
    Uint32 lost;

    while (_keep_running) {
        std::shared_ptr<Message> msg;
        while (recv_message.try_pop(msg)) {
            if (msg) {
                msg->run(message_handler);
            }
        }

        frame_end = SDL_GetTicks();
        rest_time = rate - (frame_end - frame_start);

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

MessageRunner::~MessageRunner() = default;
