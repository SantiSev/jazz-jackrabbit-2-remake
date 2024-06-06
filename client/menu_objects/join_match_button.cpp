#include "join_match_button.h"

JoinMatchButton::JoinMatchButton(SDL_Renderer* renderer,
                                 std::shared_ptr<engine::ResourcePool> resource_pool,
                                 SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                                 std::atomic<bool>& match_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Join Match", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        menu_running(menu_running),
        match_running(match_running) {}

void JoinMatchButton::on_click() {
    std::cout << "Joining match." << std::endl;
    menu_running.store(false);
    match_running.store(true);
}

JoinMatchButton::~JoinMatchButton() = default;
