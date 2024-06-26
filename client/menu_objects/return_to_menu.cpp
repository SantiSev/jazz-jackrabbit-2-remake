#include "return_to_menu.h"

ReturnToMenuButton::ReturnToMenuButton(SDL_Renderer* renderer,
                                       std::shared_ptr<engine::ResourcePool> resource_pool,
                                       SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                                       std::atomic<bool>& match_select_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), {d_rect.x, d_rect.y, 50, d_rect.h},
                               {255, 255, 255, 255}, {0, 0, 0, 255}, "Return to menu", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        menu_running(menu_running),
        match_select_running(match_select_running) {}

void ReturnToMenuButton::on_click() {
#ifdef LOG
    std::cout << "Clicked Return to menu." << std::endl;
#endif
    menu_running.store(true);
    match_select_running.store(false);
}

ReturnToMenuButton::~ReturnToMenuButton() {}
