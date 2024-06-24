#ifndef TP_FINAL_RECEIVE_MATCHES_BUTTON_H
#define TP_FINAL_RECEIVE_MATCHES_BUTTON_H

#include <atomic>
#include <memory>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../protocol/client_message_handler.h"

class ReceiveMatchesButton: public engine::Button {
private:
    std::atomic<bool>& game_running;
    std::atomic<bool>& match_select_running;
    ClientMessageHandler& message_handler;

public:
    ReceiveMatchesButton(SDL_Renderer* renderer,
                         std::shared_ptr<engine::ResourcePool> resource_pool,
                         ClientMessageHandler& message_handler, std::atomic<bool>& game_running,
                         std::atomic<bool>& match_select_running, SDL_Rect& d_rect);

    void on_click() override;

    ~ReceiveMatchesButton() override;
};


#endif
