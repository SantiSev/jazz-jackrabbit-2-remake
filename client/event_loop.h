#ifndef TP_FINAL_EVENT_LOOP_H
#define TP_FINAL_EVENT_LOOP_H

#include <memory>

#include <SDL2/SDL.h>

#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../game_engine/controllers/keyboard.h"
#include "../game_engine/controllers/mouse.h"
#include "protocol/client_message_handler.h"
#include "protocol/client_protocol.h"

class EventLoop: public Thread {
private:
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;
    SDL_Event event;
    ClientMessageHandler& message_handler;

public:
    engine::Keyboard keyboard;
    engine::Mouse mouse;
    Queue<std::shared_ptr<Message>> recv_message;

    explicit EventLoop(std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                       ClientMessageHandler& message_handler);

    void run() override;

    ~EventLoop() override;
};


#endif
