#include "menu.h"

MenuScene::MenuScene(engine::Window& window, EventLoop* event_loop,
                     std::shared_ptr<engine::ResourcePool> resource_pool,
                     std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     std::atomic<bool>& match_running, ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(nullptr),
        game_running(game_running),
        menu_running(menu_running),
        match_running(match_running) {
    // Create background
    SDL_Rect background_s_rect = {16, 16, 640, 480};
    SDL_Rect background_d_rect = {0, 0, 800, 600};
    background = new engine::Sprite(resource_pool->get_texture(BACKGROUNDS), background_s_rect,
                                    background_d_rect);

    // Create buttons
    SDL_Rect create_match_button_d_rect = {300, 300, 200, 50};
    CreateMatchButton* create_match_button =
            new CreateMatchButton(renderer, resource_pool, create_match_button_d_rect, menu_running,
                                  match_running, message_handler);
    buttons.push_back(create_match_button);

    SDL_Rect join_match_button_d_rect = {300, 370, 200, 50};
    JoinMatchButton* join_match_button =
            new JoinMatchButton(renderer, resource_pool, join_match_button_d_rect, menu_running,
                                match_running, message_handler);
    buttons.push_back(join_match_button);

    SDL_Rect quit_button_d_rect = {300, 440, 200, 50};
    QuitButton* quit_button = new QuitButton(renderer, resource_pool, quit_button_d_rect,
                                             game_running, menu_running, message_handler);
    buttons.push_back(quit_button);
}

void MenuScene::start() {
    // Add buttons to mouse signal of event loop
    for (auto button: buttons) {
        event_loop->mouse.add_on_click_signal_obj(button);
    }

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

    // Disconnect from mouse signals
    for (auto button: buttons) {
        event_loop->mouse.remove_on_click_signal_obj(button);
    }
}

MenuScene::~MenuScene() {
    // Free memory
    delete background;
    for (auto button: buttons) {
        delete button;
    }
}
