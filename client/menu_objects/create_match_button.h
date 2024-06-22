#ifndef TP_FINAL_CREATE_MATCH_BUTTON_H
#define TP_FINAL_CREATE_MATCH_BUTTON_H

#include <memory>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../protocol/client_message_handler.h"

class CreateMatchButton: public engine::Button {
private:
    std::shared_ptr<engine::ResourcePool>& resource_pool;
    std::atomic<bool>& character_select_running;

public:
    CreateMatchButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                      SDL_Rect& d_rect, std::atomic<bool>& character_select_running);

    void on_click() override;

    ~CreateMatchButton() override;
};


#endif  // TP_FINAL_CREATE_MATCH_BUTTON_H
