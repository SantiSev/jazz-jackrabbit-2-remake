#ifndef TP_FINAL_MATCH_SELECTOR_H
#define TP_FINAL_MATCH_SELECTOR_H

#include <memory>
#include <string>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../protocol/client_message_handler.h"

class MatchSelectorButton: public engine::Button {
private:
    std::atomic<bool>& match_select_running;
    std::atomic<bool>& caracter_select_running;
    uint16_t& selected_id;
    uint16_t& id_match;

public:
    MatchSelectorButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                        SDL_Rect& d_rect, std::atomic<bool>& match_select_running,
                        std::atomic<bool>& caracter_select_running, const std::string& label_info,
                        uint16_t& selected_id, uint16_t& id_match);

    void on_click() override;

    ~MatchSelectorButton() override;
};


#endif
