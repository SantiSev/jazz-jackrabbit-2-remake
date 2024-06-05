#ifndef TP_FINAL_JOIN_MATCH_BUTTON_H
#define TP_FINAL_JOIN_MATCH_BUTTON_H

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../assets.h"

class JoinMatchButton: public engine::Button {
public:
    JoinMatchButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                    SDL_Rect& d_rect);

    void on_click() override;

    ~JoinMatchButton() override;
};


#endif  // TP_FINAL_JOIN_MATCH_BUTTON_H
