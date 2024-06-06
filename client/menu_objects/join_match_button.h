#ifndef TP_FINAL_JOIN_MATCH_BUTTON_H
#define TP_FINAL_JOIN_MATCH_BUTTON_H

#include <atomic>
#include <memory>

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../assets.h"

class JoinMatchButton: public engine::Button {
private:
    std::atomic<bool>& menu_running;
    std::atomic<bool>& match_running;


public:
    JoinMatchButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                    SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                    std::atomic<bool>& match_running);

    void on_click() override;

    ~JoinMatchButton() override;
};


#endif  // TP_FINAL_JOIN_MATCH_BUTTON_H
