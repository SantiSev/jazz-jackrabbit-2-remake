#ifndef TP_FINAL_RETURN_MENU_BUTTON_H
#define TP_FINAL_RETURN_MENU_BUTTON_H

#include <atomic>
#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../protocol/client_message_handler.h"

class ReturnMenuButton: public engine::Button {
private:
    std::atomic<bool>& menu_running;
    std::atomic<bool>& scoreboard_running;
    ClientMessageHandler& message_handler;

public:
    ReturnMenuButton(SDL_Renderer* renderer,
                     const std::shared_ptr<engine::ResourcePool>& resource_pool, SDL_Rect& d_rect,
                     std::atomic<bool>& menu_running, std::atomic<bool>& scoreboard_running,
                     ClientMessageHandler& message_handler);

    void on_click() override;

    ~ReturnMenuButton() override;
};


#endif
