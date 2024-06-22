#include "create_match_button.h"

CreateMatchButton::CreateMatchButton(SDL_Renderer* renderer,
                                     std::shared_ptr<engine::ResourcePool> resource_pool,
                                     SDL_Rect& d_rect, std::atomic<bool>& character_select_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Create Match", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        resource_pool(resource_pool),
        character_select_running(character_select_running) {}

void CreateMatchButton::on_click() {
#ifdef LOG
    std::cout << "Clicked Create match." << std::endl;
#endif
    character_select_running.store(true);  // move to next stage of match creation
}

CreateMatchButton::~CreateMatchButton() = default;
