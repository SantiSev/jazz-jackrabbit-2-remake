#include "quit_button.h"

QuitButton::QuitButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                       SDL_Rect& d_rect, std::atomic<bool>& game_running,
                       std::atomic<bool>& menu_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Quit", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        game_running(game_running),
        menu_running(menu_running) {}

void QuitButton::on_click() {
    std::cout << "Closing game." << std::endl;
    menu_running.store(false);
    game_running.store(false);
}

QuitButton::~QuitButton() {}
