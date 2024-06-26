#include "map_select_scene.h"

#define X_START 300
#define Y_START 200

MapSelectScene::MapSelectScene(engine::Window& window, EventLoop* event_loop,
                               std::shared_ptr<engine::ResourcePool> resource_pool,
                               std::atomic<bool>& game_running,
                               std::atomic<bool>& map_select_running,
                               std::atomic<bool>& character_select_running,
                               ClientMessageHandler& message_handler, uint16_t& selected_map_id):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(nullptr),
        title(resource_pool->get_font(FONT), SDL_Rect{170, 100, 450, 75},
              SDL_Color{255, 255, 255, 255}, SDL_Color{255, 255, 255, 255}, "Select a Map",
              renderer),
        title_background(SDL_Color{0, 122, 16, 255}, SDL_Rect{0, 90, VIEWPORT_WIDTH, 85}),
        game_running(game_running),
        map_select_running(map_select_running),
        character_select_running(character_select_running),
        message_handler(message_handler),
        selected_map_id(selected_map_id) {
    auto texture = resource_pool->get_texture(CHARACTER_SELECT_FILE);
    auto yaml = *resource_pool->get_yaml(CHARACTER_SELECT_FILE);

    SDL_Rect back_s_rect = {yaml["character_select_background"]["x"].as<int>(),
                            yaml["character_select_background"]["y"].as<int>(),
                            yaml["character_select_background"]["w"].as<int>(),
                            yaml["character_select_background"]["h"].as<int>()};

    background = std::make_unique<engine::Sprite>(
            texture, back_s_rect, SDL_Rect{0, 0, window.get_width(), window.get_height()});

    create_buttons();
}

void MapSelectScene::create_buttons() {
    auto yaml = *resource_pool->get_yaml(MAPS_FILE);
    auto map_list = yaml["map_list"];

    int x_start = X_START;
    int y_start = Y_START;

    for (auto map: map_list) {
        std::string map_name = map["name"].as<std::string>();
        uint16_t map_id = map["id"].as<uint16_t>();
        selectors.emplace_back(renderer, resource_pool, map_name, map_id, x_start, y_start,
                               selected_map_id, map_select_running, character_select_running);
        selectors.back().center_x(0, VIEWPORT_WIDTH);
        y_start += 50;
    }
}

void MapSelectScene::start() {
#ifdef LOG
    std::cout << "Starting map select scene..." << std::endl;
#endif

    for (auto& selector: selectors) {
        event_loop->mouse.add_on_click_signal_obj(&selector);
    }

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

MapSelectScene::~MapSelectScene() {
    for (auto& selector: selectors) {
        event_loop->mouse.remove_on_click_signal_obj(&selector);
    }
}
