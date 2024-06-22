#include "map_select_scene.h"

MapSelectScene::MapSelectScene(engine::Window& window, EventLoop* event_loop,
                                           std::shared_ptr<engine::ResourcePool> resource_pool,
                                           std::atomic<bool>& game_running,
                                           std::atomic<bool>& map_select_running,
                                           ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(nullptr),
        title(resource_pool->get_font(FONT), SDL_Rect{100, 100, 600, 75},
              SDL_Color{255, 255, 255, 255}, SDL_Color{255, 255, 255, 255}, "Select a Map",
              renderer),
        title_background(SDL_Color{0, 122, 16, 255}, SDL_Rect{0, 90, 800, 85}),
        game_running(game_running),
        map_select_running(map_select_running),
        message_handler(message_handler),
        selected_map_id(1) {
    auto texture = resource_pool->get_texture(CHARACTER_SELECT_FILE);
    auto yaml = *resource_pool->get_yaml(CHARACTER_SELECT_FILE);

    SDL_Rect back_s_rect = {yaml[CHARACTER_SELECT_BACKGROUND]["x"].as<int>(),
                            yaml[CHARACTER_SELECT_BACKGROUND]["y"].as<int>(),
                            yaml[CHARACTER_SELECT_BACKGROUND]["w"].as<int>(),
                            yaml[CHARACTER_SELECT_BACKGROUND]["h"].as<int>()};

    background = std::make_unique<engine::Sprite>(
            texture, back_s_rect, SDL_Rect{0, 0, window.get_width(), window.get_height()});

    create_buttons();

    for (auto& selector: selectors) {
        event_loop->mouse.add_on_click_signal_obj(&selector);
    }
}

void MapSelectScene::create_buttons() {
    selectors.emplace_back(resource_pool, SOME_MAP, X, Y, selected_map_id,
                           map_select_running);
}

void MapSelectScene::start() {
    const Uint32 rate = 1000 / 60;

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;
    int it = 0;

    // Drop & Rest
    while (game_running && map_select_running) {
        // Draw
        window.clear();
        background->draw(renderer, it);
        title_background.draw(renderer, it);
        title.draw(renderer, it);
        for (auto& selector: selectors) {
            selector.draw(renderer, it);
        }
        window.render();

        frame_end = SDL_GetTicks();
        int rest_time = rate - (frame_end - frame_start);

        if (rest_time < 0) {
            behind = -rest_time;
            rest_time = rate - (behind % rate);
            lost = behind / rate;
            frame_start += lost;
            it += std::floor(lost / rate);
        }

        SDL_Delay(rest_time);
        frame_start += rate;
        it++;
    }
}

MapSelectScene::~MapSelectScene() {
    for (auto& selector: selectors) {
        event_loop->mouse.remove_on_click_signal_obj(&selector);
    }
}