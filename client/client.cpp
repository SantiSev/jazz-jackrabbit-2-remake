#include "client.h"

Client::Client(const std::string& host, const std::string& port):
        message_handler(),
        window(800, 600, true, true),
        resource_pool(std::make_shared<engine::ResourcePool>(window.get_renderer())),
        game_running(true),
        menu_running(true),
        match_running(false),
        event_loop(new EventLoop(game_running, menu_running, message_handler)),
        thread_manager(new ClientThreadManager(host, port, event_loop->recv_message,
                                               message_handler.send_message)) {
    // Pre-load necessary resources
    pre_load_resources(resource_pool);
}

void Client::start() {
    Menu menu(window, event_loop, resource_pool, game_running, menu_running);

    event_loop->start();

    while (game_running) {
        menu.start();
        if (match_running) {
            // Match match(window, event_loop, resource_pool, game_running, match_running);
            // match.start();
        }
    }

    //    std::list<engine::CanvasObject*> objects;
    //
    //    SDL_Rect rect = {19, 32, 61, 59};
    //    SDL_Rect d_rect = {0, 0, 450, 590};
    //    engine::AnimatedSprite sprite(resource_pool.get_texture("assets/jazz_test.png"), rect,
    //    d_rect,
    //                                  6, 8);
    //    Player player(std::move(sprite));
    //    objects.push_back(&player);
    //
    //    event_loop->keyboard.add_on_key_down_signal_obj(&player);
    //    event_loop->mouse.add_on_click_signal_obj(&player);
    //
    //    event_loop->start();
    //
    //    Uint32 frame_start = 0;
    //    Uint32 frame_time = 0;
    //    const int frame_delay = 1000 / 60;
    //
    //    while (game_running) {
    //        // Updates
    //        int delta_time = SDL_GetTicks() - frame_start;
    //        for (auto object: objects) {
    //            object->update(delta_time);
    //        }
    //
    //        frame_start = SDL_GetTicks();
    //
    //        // Draw
    //        window.clear();
    //        for (auto object: objects) {
    //            object->draw(renderer);
    //        }
    //        window.render();
    //
    //        frame_time = SDL_GetTicks() - frame_start;
    //        if (frame_delay > frame_time) {  // Delay to achieve desired fps
    //            SDL_Delay(frame_delay - frame_time);
    //        }
    //    }
}

void Client::pre_load_resources(std::shared_ptr<engine::ResourcePool>& resource_pool) {
    // Textures
    resource_pool->load_texture(BACKGROUNDS);
    resource_pool->load_texture(JAZZ);
    resource_pool->load_texture("assets/jazz_test.png");

    // Fonts
    resource_pool->load_font(FONT, FONT_SIZE);
}

Client::~Client() {
    event_loop->stop();
    event_loop->join();
    delete thread_manager;
    delete event_loop;
}
