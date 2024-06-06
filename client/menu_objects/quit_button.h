#ifndef TP_FINAL_QUITBUTTON_H
#define TP_FINAL_QUITBUTTON_H

#include <atomic>
#include <memory>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../assets.h"
#include "../protocol/client_message_handler.h"


class QuitButton: public engine::Button {
private:
    std::atomic<bool>& game_running;
    std::atomic<bool>& menu_running;
    ClientMessageHandler& message_handler;

public:
    QuitButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
               SDL_Rect& d_rect, std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
               ClientMessageHandler& message_handler);

    void on_click() override;

    ~QuitButton() override;
};


#endif  // TP_FINAL_QUITBUTTON_H
