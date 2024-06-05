#include "menu.h"

Menu::Menu(engine::Window& window, EventLoop* event_loop,
           std::shared_ptr<engine::ResourcePool> resource_pool, std::atomic<bool>& game_running,
           std::atomic<bool>& menu_running):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(nullptr),
        game_running(game_running),
        menu_running(menu_running) {
    // Create background
    SDL_Rect background_s_rect = {16, 16, 640, 480};
    SDL_Rect background_d_rect = {0, 0, 800, 600};
    background = new engine::Sprite(resource_pool->get_texture(BACKGROUNDS), background_s_rect,
                                    background_d_rect);

    // Create buttons
    SDL_Rect quit_button_d_rect = {0, 0, 100, 50};
    QuitButton* quit_button =
            new QuitButton(renderer, resource_pool, quit_button_d_rect, game_running, menu_running);
    buttons.push_back(quit_button);

    // Add buttons to mouse signal of event loop
    event_loop->mouse.add_on_click_signal_obj(quit_button);
}

void Menu::start() {
    Uint32 frame_start = 0;
    Uint32 frame_time = 0;
    const int frame_delay = 1000 / 60;

    while (menu_running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        background->update(delta_time);
        for (auto button: buttons) {
            button->update(delta_time);
        }

        frame_start = SDL_GetTicks();

        // Draw
        window.clear();
        background->draw(renderer);
        for (auto button: buttons) {
            button->draw(renderer);
        }
        window.render();

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve desired fps
            SDL_Delay(frame_delay - frame_time);
        }
    }
}

Menu::~Menu() {
    // Disconnect from mouse signals
    for (auto button: buttons) {
        event_loop->mouse.remove_on_click_signal_obj(button);
    }

    // Free memory
    delete background;
    for (auto button: buttons) {
        delete button;
    }
}
