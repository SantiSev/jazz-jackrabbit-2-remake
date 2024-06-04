#include "client.h"

Client::Client(const std::string& host, const std::string& port):
        // protocol(host, port),
        game_running(true),
        event_loop(std::ref(game_running)) {}

void Client::start() {
    engine::Window window(800, 600, true, true);
    auto renderer = window.getRenderer();

    // Pre-load necessary resources
    engine::ResourcePool resource_pool(renderer);
    resource_pool.load_texture("assets/jazz.png");

    std::list<engine::CanvasObject*> objects;

    SDL_Rect rect = {0, 420, 53, 50};
    SDL_Rect d_rect = {0, 0, 800, 600};
    engine::AnimatedSprite sprite(resource_pool.get_texture("assets/jazz.png"), rect, d_rect, 13,
                                  8);
    Player player(std::move(sprite));
    objects.push_back(&player);

    event_loop.keyboard.add_on_key_down_signal_obj(&player);
    event_loop.mouse.add_on_click_signal_obj(&player);

    event_loop.start();

    Uint32 frame_start;
    Uint32 frame_time;
    const int frame_delay = 1000 / 60;

    while (game_running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        for (auto object: objects) {
            object->update(delta_time);
        }

        frame_start = SDL_GetTicks();

        // Draw
        window.clear();
        for (auto object: objects) {
            object->draw(renderer);
        }
        window.render();

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve desired fps
            SDL_Delay(frame_delay - frame_time);
        }
    }
    event_loop.join();
}

Client::~Client() = default;
