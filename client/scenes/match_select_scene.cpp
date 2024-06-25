#include "match_select_scene.h"

#define X_START 300
#define Y_START 200

MatchSelectScene::MatchSelectScene(engine::Window& window, EventLoop* event_loop,
                                   std::shared_ptr<engine::ResourcePool> resource_pool,
                                   std::shared_ptr<engine::SoundManager> sound_manager,
                                   std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                                   std::atomic<bool>& match_select_running,
                                   std::atomic<bool>& is_joinning,
                                   std::atomic<bool>& character_select_running,
                                   ClientMessageHandler& message_handler,
                                   uint16_t& joined_id_match):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(nullptr),
        title(resource_pool->get_font(FONT), SDL_Rect{170, 100, 450, 75},
              SDL_Color{255, 255, 255, 255}, SDL_Color{255, 255, 255, 255}, "Select a Match",
              renderer),
        title_background(SDL_Color{0, 122, 16, 255}, SDL_Rect{0, 90, VIEWPORT_WIDTH, 85}),
        sound_manager(sound_manager),
        game_running(game_running),
        menu_running(menu_running),
        match_select_running(match_select_running),
        character_select_running(character_select_running),
        match_requested(false),
        is_joinning(is_joinning),
        message_handler(message_handler),
        selected_id(joined_id_match) {
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

void MatchSelectScene::start() {
    // Add buttons to mouse signal of event loop
    for (auto& button: buttons) {
        event_loop->mouse.add_on_click_signal_obj(button);
    }

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;
    int it = 0;

    match_requested = true;
    message_handler.send_match_list_request();

    // Drop & Rest
    while (game_running && match_select_running) {
        // Draw
        window.clear();
        background->draw(renderer, it);
        title_background.draw(renderer, it);
        title.draw(renderer, it);
        if (match_requested) {
            show_matches();
        }
        for (auto button: buttons) {
            button->draw(renderer, it);
        }
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
    clear_list_buttons();
    for (auto button: buttons) {
        event_loop->mouse.remove_on_click_signal_obj(button);
    }
}

void MatchSelectScene::create_buttons() {
    // Create buttons
    SDL_Rect receive_matches_button_d_rect = {X_START, Y_START - 150, 150, 35};
    ReceiveMatchesButton* receive_matches_button =
            new ReceiveMatchesButton(renderer, resource_pool, message_handler,
                                     receive_matches_button_d_rect, match_requested);

    //    SDL_Rect return_button_d_rect = {300, y_start - 50, w, h};
    //    ReturnToMenuButton* return_to_menu_button =
    //            new ReturnToMenuButton(renderer, resource_pool,return_button_d_rect, menu_running,
    //            match_select_running);

    // Add buttons to list
    buttons.push_back(receive_matches_button);
    buttons.back()->center_x(0, VIEWPORT_WIDTH);
    //    buttons.push_back(return_to_menu_button);
}

void MatchSelectScene::show_matches() {
    std::shared_ptr<MatchInfoDTO> match_info = nullptr;
    message_handler.match_select_q.try_pop(match_info);
    if (match_info) {
        clear_list_buttons();
        create_match_buttons(match_info);
        match_requested = false;
    }
}

void MatchSelectScene::create_match_buttons(const std::shared_ptr<MatchInfoDTO>& dto) {
    int x_start = X_START;
    int y_start = Y_START;

    int num_matches = dto->num_games;

    for (int i = 0; i < num_matches; i++) {
        if (dto->active_games[i].players_ingame == dto->active_games[i].players_max) {
            continue;
        }
        std::string map_str = get_map_name(dto->active_games[i].map_id);

        std::string label_info =
                map_str + " - Players: " + std::to_string(dto->active_games[i].players_ingame) +
                "/" + std::to_string(dto->active_games[i].players_max);
        uint16_t id = dto->active_games[i].match_id;
        selectors.emplace_back(renderer, resource_pool, x_start, y_start, match_select_running,
                               character_select_running, is_joinning, label_info, id, selected_id);
        selectors.back().center_x(0, VIEWPORT_WIDTH);
        event_loop->mouse.add_on_click_signal_obj(&selectors.back());
        y_start += 50;
    }
}

std::string MatchSelectScene::get_map_name(int map_id) {
    YAML::Node node = *resource_pool->get_yaml(MAPS_FILE);
    const YAML::Node& map_list = node["map_list"];

    auto it = std::find_if(map_list.begin(), map_list.end(), [map_id](const YAML::Node& map_node) {
        return map_node["id"].as<int>() == map_id;
    });
    if (it != map_list.end()) {
        return (*it)["name"].as<std::string>();
    }
    throw std::runtime_error("Map ID not found in map_list");
}

void MatchSelectScene::clear_list_buttons() {
    for (auto& selector: selectors) {
        event_loop->mouse.remove_on_click_signal_obj(&selector);
    }
    selectors.clear();
}

MatchSelectScene::~MatchSelectScene() {
    for (auto button: buttons) {
        event_loop->mouse.remove_on_click_signal_obj(button);
        delete button;
    }
    clear_list_buttons();
}
