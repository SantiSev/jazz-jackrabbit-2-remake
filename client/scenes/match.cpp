#include "match.h"

MatchScene::MatchScene(engine::Window& window, EventLoop* event_loop,
                       std::shared_ptr<engine::ResourcePool> resource_pool,
                       std::atomic<bool>& match_running):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        match_running(match_running),
        map(MAP1_TILESET, MAP1_YAML, resource_pool) {}

void MatchScene::start() {
    Uint32 frame_start = 0;
    Uint32 frame_time = 0;
    const int frame_delay = 1000 / 60;

    while (match_running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        map.update(delta_time);
        // for (auto player: players) {
        //     player->update(delta_time);
        // }

        frame_start = SDL_GetTicks();

        // Draw
        window.clear();
        map.draw(renderer);
        // for (auto player: players) {
        //     player->draw(renderer);
        // }

        window.render();
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}

MatchScene::~MatchScene() {
    // Disconnect from mouse signals
    // for (auto player: players) {
    //     event_loop->keyboard.remove_on_key_down_signal_obj(player);
    //     event_loop->mouse.remove_on_click_signal_obj(player);
    // }
}
