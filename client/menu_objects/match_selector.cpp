#include "match_selector.h"

MatchSelectorButton::MatchSelectorButton(SDL_Renderer* renderer,
                                         std::shared_ptr<engine::ResourcePool> resource_pool,
                                         SDL_Rect& d_rect, std::atomic<bool>& match_select_running,
                                         std::atomic<bool>& caracter_select_running,
                                         const std::string& label_info, uint16_t& selected_id,
                                         uint16_t& id_match):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, label_info, renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        match_select_running(match_select_running),
        caracter_select_running(caracter_select_running),
        selected_id(selected_id),
        id_match(id_match) {}


void MatchSelectorButton::on_click() {
#ifdef LOG
    std::cout << "Clicked Join match." << std::endl;
#endif
    selected_id = id_match;
    caracter_select_running.store(true);
    match_select_running.store(false);
}

MatchSelectorButton::~MatchSelectorButton() = default;
