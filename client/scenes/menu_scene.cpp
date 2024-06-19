#include "menu_scene.h"

#define Y_BUTTON_START 200
#define BUTTON_MARGIN 10
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 25

MenuScene::MenuScene(engine::Window& window, EventLoop* event_loop,
                     std::shared_ptr<engine::ResourcePool> resource_pool,
                     std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                     std::atomic<bool>& editor_running, ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(std::make_unique<MainScreenBackground>(*resource_pool)),
        game_running(game_running),
        menu_running(menu_running),
        editor_running(editor_running) {

    create_buttons(message_handler);
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

void MenuScene::create_buttons(ClientMessageHandler& message_handler) {

    int y_start = Y_BUTTON_START;
    int w = BUTTON_WIDTH;
    int h = BUTTON_HEIGHT;

    // Create buttons
    SDL_Rect create_match_button_d_rect = {0, y_start, w, h};
    CreateMatchButton* create_match_button = new CreateMatchButton(
            renderer, resource_pool, create_match_button_d_rect, message_handler);
    y_start += h + BUTTON_MARGIN;

    SDL_Rect join_match_button_d_rect = {0, y_start, w, h};
    JoinMatchButton* join_match_button =
            new JoinMatchButton(renderer, resource_pool, join_match_button_d_rect, message_handler);
    y_start += h + BUTTON_MARGIN;

    SDL_Rect map_editor_d_rect = {0, y_start, w, h};
    EditorButton* map_editor = new EditorButton(renderer, resource_pool, map_editor_d_rect,
                                                menu_running, editor_running);
    y_start += h + BUTTON_MARGIN;

    SDL_Rect quit_button_d_rect = {0, y_start, w, h};
    QuitButton* quit_button = new QuitButton(renderer, resource_pool, quit_button_d_rect,
                                             game_running, menu_running, message_handler);

    // Add buttons to list
    buttons.push_back(create_match_button);
    buttons.push_back(join_match_button);
    buttons.push_back(map_editor);
    buttons.push_back(quit_button);

    // Center buttons
    for (auto button: buttons) {
        button->center_x(0, window.get_width());
    }
}

MenuScene::~MenuScene() {
    // Free memory
    for (auto button: buttons) {
        delete button;
    }
}
