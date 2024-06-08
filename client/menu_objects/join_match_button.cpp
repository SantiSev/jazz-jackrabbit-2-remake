#include "join_match_button.h"

JoinMatchButton::JoinMatchButton(SDL_Renderer* renderer,
                                 std::shared_ptr<engine::ResourcePool> resource_pool,
                                 SDL_Rect& d_rect, ClientMessageHandler& message_handler):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Join Match", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        message_handler(message_handler) {}

void JoinMatchButton::on_click() {
    std::cout << "Joining match." << std::endl;
    message_handler.join_match(1, JAZZ_CHARACTER);
}

JoinMatchButton::~JoinMatchButton() = default;
