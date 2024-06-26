#ifndef TP_FINAL_RETURN_TO_MENU_H
#define TP_FINAL_RETURN_TO_MENU_H

#include <atomic>
#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../protocol/client_message_handler.h"

class ReturnToMenuButton: public engine::Button {
private:
    std::atomic<bool>& menu_running;
    std::atomic<bool>& match_select_running;

public:
    ReturnToMenuButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                       SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                       std::atomic<bool>& match_select_running);

    void on_click() override;

    ~ReturnToMenuButton() override;
};


#endif
