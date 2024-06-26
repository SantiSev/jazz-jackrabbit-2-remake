#include "receive_matches_button.h"

ReceiveMatchesButton::ReceiveMatchesButton(SDL_Renderer* renderer,
                                           std::shared_ptr<engine::ResourcePool> resource_pool,
                                           ClientMessageHandler& message_handler, SDL_Rect& d_rect,
                                           std::atomic<bool>& match_requested):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {255, 255, 255, 255}, "Refresh", renderer)),
                       {d_rect.x, d_rect.y, d_rect.w + 15, d_rect.h}, {0, 150, 0, 255},
                       {0, 0, 40, 255}),
        match_requested(match_requested),
        message_handler(message_handler) {}

void ReceiveMatchesButton::on_click() {
    message_handler.send_match_list_request();
    match_requested.store(true);
}

ReceiveMatchesButton::~ReceiveMatchesButton() = default;
