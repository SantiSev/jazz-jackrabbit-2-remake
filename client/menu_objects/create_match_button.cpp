#include "create_match_button.h"

CreateMatchButton::CreateMatchButton(SDL_Renderer* renderer,
                                     std::shared_ptr<engine::ResourcePool> resource_pool,
                                     SDL_Rect& d_rect, std::atomic<bool>& map_select_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Create Match", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        resource_pool(resource_pool),
        map_select_running(map_select_running) {}

void CreateMatchButton::on_click() {
#ifdef LOG
    std::cout << "Clicked Create match." << std::endl;
#endif
    map_select_running.store(true);  // move to next stage of match creation
}

CreateMatchButton::~CreateMatchButton() = default;
