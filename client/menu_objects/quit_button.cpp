#include "quit_button.h"

QuitButton::QuitButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                       SDL_Rect& d_rect):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Quit", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}) {}

void QuitButton::on_click() { std::cout << "ATUUUUUUS" << std::endl; }

QuitButton::~QuitButton() {}
