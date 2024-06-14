#include "menu_scene.h"

MenuScene::MenuScene(engine::Window& window, EventLoop* event_loop,
                     std::shared_ptr<engine::ResourcePool> resource_pool,
                     std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     ClientMessageHandler& message_handler):
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
    SDL_Rect create_match_button_d_rect = {300, 300, 200, 50};
    CreateMatchButton* create_match_button = new CreateMatchButton(
            renderer, resource_pool, create_match_button_d_rect, message_handler);
    buttons.push_back(create_match_button);

    SDL_Rect join_match_button_d_rect = {300, 370, 200, 50};
    JoinMatchButton* join_match_button =
            new JoinMatchButton(renderer, resource_pool, join_match_button_d_rect, message_handler);
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

    const Uint32 rate = 1000 / 60;

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;
    int it = 0;

    // Drop & Rest
    while (menu_running) {
        // Draw
        window.clear();
        background->draw(renderer, it);
        for (auto button: buttons) {
            button->draw(renderer, it);
        }
        window.render();

        frame_end = SDL_GetTicks();
        int rest_time = rate - (frame_end - frame_start);

        if (rest_time < 0) {
            behind = -rest_time;
            rest_time = rate - (behind % rate);
            lost = behind / rate;
            frame_start += lost;
            it = std::round(lost / rate);
        }

        SDL_Delay(rest_time);
        frame_start += rate;
        it++;
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
