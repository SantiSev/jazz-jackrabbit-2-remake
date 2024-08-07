#include "editor_scene.h"

EditorScene::EditorScene(engine::Window& window, EventLoop* event_loop,
                         std::shared_ptr<engine::ResourcePool> resource_pool,
                         std::atomic<bool>& menu_running, std::atomic<bool>& editor_running,
                         ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        menu_running(menu_running),
        editor_running(editor_running),
        background(nullptr),
        tile_manager(resource_pool, event_loop, tiles),
        hud(renderer, resource_pool, event_loop, tile_manager, menu_running, editor_running),
        camera(window.get_width(), hud.get_body().y, 0,
               resource_pool->get_config()->map_ed_max_width, 0,
               resource_pool->get_config()->map_ed_max_height),
        controller(camera, event_loop) {
#ifdef LOG
    std::cout << "Constructing editor scene..." << std::endl;
#endif
    load_background();
}

void EditorScene::start() {
#ifdef LOG
    std::cout << "Starting editor scene..." << std::endl;
#endif

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;
    int it = 0;

    // Drop & Rest
    while (editor_running) {
        // Draw
        window.clear();
        background->draw(renderer, it);
        for (auto& tile: tiles) {
            bool is_visible = camera.adjust_relative_position(*tile.second);
            tile.second->visible.store(is_visible);
            if (is_visible) {
                tile.second->draw(renderer, it);
            }
        }
        hud.draw(renderer, it);
        window.render();

        frame_end = SDL_GetTicks();
        int rest_time = RATE - (frame_end - frame_start);

        if (rest_time < 0) {
            behind = -rest_time;
            rest_time = RATE - (behind % RATE);
            lost = behind / RATE;
            frame_start += lost;
            it += std::floor(lost / RATE);
        }

        SDL_Delay(rest_time);
        frame_start += RATE;
        it++;
    }
}

void EditorScene::load_background() {
    auto texture = resource_pool->get_texture(EDITOR_FILE);
    auto yaml = *resource_pool->get_yaml(EDITOR_FILE);

    auto background_yaml = yaml["background"];
    SDL_Rect back_s_rect = {background_yaml["x"].as<int>(), background_yaml["y"].as<int>(),
                            background_yaml["w"].as<int>(), background_yaml["h"].as<int>()};
    SDL_Rect back_d_rect = {0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT};
    background = std::make_unique<engine::Sprite>(texture, back_s_rect, back_d_rect);
}

EditorScene::~EditorScene() {
    for (auto& tile: tiles) {
        event_loop->mouse.remove_on_click_signal_obj(tile.second.get());
    }
}
