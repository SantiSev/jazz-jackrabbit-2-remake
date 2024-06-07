#include "create_match_button.h"

CreateMatchButton::CreateMatchButton(SDL_Renderer* renderer,
                                     std::shared_ptr<engine::ResourcePool> resource_pool,
                                     SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                                     std::atomic<bool>& match_running,
                                     ClientMessageHandler& message_handler):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Create Match", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        menu_running(menu_running),
        match_running(match_running),
        message_handler(message_handler) {}

void CreateMatchButton::on_click() {
    std::cout << "Creating match." << std::endl;
    message_handler.create_match(JAZZ_CHARACTER, MAP_1, MAX_PLAYERS);
    menu_running.store(false);
    match_running.store(true);
}

CreateMatchButton::~CreateMatchButton() = default;
