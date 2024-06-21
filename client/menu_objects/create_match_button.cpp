#include "create_match_button.h"

CreateMatchButton::CreateMatchButton(SDL_Renderer* renderer,
                                     std::shared_ptr<engine::ResourcePool> resource_pool,
                                     SDL_Rect& d_rect, ClientMessageHandler& message_handler):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Create Match", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        resource_pool(resource_pool),
        message_handler(message_handler) {}

void CreateMatchButton::on_click() {
#ifdef LOG
    std::cout << "Clicked Create match." << std::endl;
#endif
    message_handler.create_match(LORI_CHARACTER, (uint16_t)1, MAX_PLAYERS);
}

CreateMatchButton::~CreateMatchButton() = default;
