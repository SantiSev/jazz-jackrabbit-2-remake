#include "receive_matches_button.h"

ReceiveMatchesButton::ReceiveMatchesButton(SDL_Renderer* renderer,
                                           std::shared_ptr<engine::ResourcePool> resource_pool,
                                           ClientMessageHandler& message_handler,
                                           std::atomic<bool>& game_running,
                                           std::atomic<bool>& match_select_running,
                                           SDL_Rect& d_rect):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Find Online Matches", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        game_running(game_running),
        match_select_running(match_select_running),
        message_handler(message_handler) {}

void ReceiveMatchesButton::on_click() { message_handler.send_match_list_request(); }

ReceiveMatchesButton::~ReceiveMatchesButton() = default;
