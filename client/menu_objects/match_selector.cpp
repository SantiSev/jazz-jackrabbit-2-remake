#include "match_selector.h"

MatchSelector::MatchSelector(SDL_Renderer* renderer,
                             std::shared_ptr<engine::ResourcePool> resource_pool, int x, int y,
                             std::atomic<bool>& match_select_running,
                             std::atomic<bool>& caracter_select_running,
                             std::atomic<bool>& is_joinning, const std::string& label_info,
                             uint16_t id_match, uint16_t& selected_id):
        engine::Button(std::make_unique<engine::Label>(
                               engine::Label(resource_pool->get_font(FONT), {x, y + 5, 280, 30},
                                             {0, 0, 0, 255}, {0, 0, 0, 255}, label_info, renderer)),
                       {x, y, 330, 40}, get_random_color(), get_random_color()),
        match_select_running(match_select_running),
        caracter_select_running(caracter_select_running),
        is_joinning(is_joinning),
        selected_id(selected_id),
        id_match(id_match) {}

void MatchSelector::on_click() {
#ifdef LOG
    std::cout << "Clicked Join match." << std::endl;
#endif
    selected_id = id_match;
    is_joinning.store(true);
    caracter_select_running.store(true);
    match_select_running.store(false);
}

SDL_Color MatchSelector::get_random_color() {
    const Uint8 minBrightValue = 128;
    Uint8 r = minBrightValue + rand() % (256 - minBrightValue);
    Uint8 g = minBrightValue + rand() % (256 - minBrightValue);
    Uint8 b = minBrightValue + rand() % (256 - minBrightValue);
    return SDL_Color{r, g, b, 255};
}

MatchSelector::~MatchSelector() = default;
