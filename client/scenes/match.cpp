#include "match.h"

MatchScene::MatchScene(engine::Window& window, EventLoop* event_loop,
                       std::shared_ptr<engine::ResourcePool> resource_pool,
                       std::atomic<bool>& match_running, ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        match_running(match_running),
        map(nullptr),
        game_state_q(message_handler.game_state_q) {}

void MatchScene::start() {

    if (map == nullptr) {
        SDL_Delay(1000);
    }

    Uint32 frame_start = 0;
    Uint32 frame_time;
    const int frame_delay = 1000 / 60;

    while (match_running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        map->update(delta_time);
        // for (auto player: players) {
        //     player->update(delta_time);
        // }

        frame_start = SDL_GetTicks();

        // Draw
        window.clear();
        map->draw(renderer);
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

void MatchScene::load_map(const map_list_t& map_enum) {
    map = std::make_unique<Map>(map_enum, resource_pool);
}

void MatchScene::create_objects() {
    // for (auto player: players) {
    //     player->create_objects(renderer, resource_pool);
    // }
}

void MatchScene::update_objects() {
    // for (auto player: players) {
    //     player->update_objects();
    // }
}

MatchScene::~MatchScene() {
    // Disconnect from mouse signals
    // for (auto player: players) {
    //     event_loop->keyboard.remove_on_key_down_signal_obj(player);
    //     event_loop->mouse.remove_on_click_signal_obj(player);
    // }
}
