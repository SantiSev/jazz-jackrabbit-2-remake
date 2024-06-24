#include "return_menu_button.h"

ReturnMenuButton::ReturnMenuButton(SDL_Renderer* renderer,
                                   const std::shared_ptr<engine::ResourcePool>& resource_pool,
                                   SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                                   std::atomic<bool>& scoreboard_running,
                                   ClientMessageHandler& message_handler):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Return To Menu", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        menu_running(menu_running),
        scoreboard_running(scoreboard_running),
        message_handler(message_handler) {}

void ReturnMenuButton::on_click() {
#ifdef LOG
    std::cout << "Clicked Close game." << std::endl;
#endif
    menu_running.store(true);
    scoreboard_running.store(false);
}

ReturnMenuButton::~ReturnMenuButton() {}
