#include "character_select_scene.h"

CharacterSelectScene::CharacterSelectScene(engine::Window& window, EventLoop* event_loop,
                                           std::shared_ptr<engine::ResourcePool> resource_pool,
                                           std::shared_ptr<engine::SoundManager> sound_manager,
                                           std::atomic<bool>& game_running,
                                           std::atomic<bool>& character_select_running,
                                           std::atomic<bool>& is_joinning,
                                           uint16_t& selected_map_id, uint16_t& match_selected_id,
                                           ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        sound_manager(sound_manager),
        background(nullptr),
        title(resource_pool->get_font(FONT), SDL_Rect{100, 100, VIEWPORT_HEIGHT, 75},
              SDL_Color{255, 255, 255, 255}, SDL_Color{255, 255, 255, 255}, "Select Your Character",
              renderer),
        title_background(SDL_Color{0, 122, 16, 255}, SDL_Rect{0, 90, VIEWPORT_WIDTH, 85}),
        game_running(game_running),
        character_select_running(character_select_running),
        selected_map_id(selected_map_id),
        match_selected_id(match_selected_id),
        is_joinning(is_joinning),
        message_handler(message_handler),
        selected_character(JAZZ_CHARACTER) {
    auto texture = resource_pool->get_texture(CHARACTER_SELECT_FILE);
    auto yaml = *resource_pool->get_yaml(CHARACTER_SELECT_FILE);

    SDL_Rect back_s_rect = {yaml[CHARACTER_SELECT_BACKGROUND]["x"].as<int>(),
                            yaml[CHARACTER_SELECT_BACKGROUND]["y"].as<int>(),
                            yaml[CHARACTER_SELECT_BACKGROUND]["w"].as<int>(),
                            yaml[CHARACTER_SELECT_BACKGROUND]["h"].as<int>()};

    background = std::make_unique<engine::Sprite>(
            texture, back_s_rect, SDL_Rect{0, 0, window.get_width(), window.get_height()});

    create_buttons();
}

void CharacterSelectScene::create_buttons() {
    selectors.emplace_back(resource_pool, JAZZ_CHARACTER, 130, 400, selected_character,
                           character_select_running);
    selectors.emplace_back(resource_pool, SPAZ_CHARACTER, 330, 400, selected_character,
                           character_select_running);
    selectors.emplace_back(resource_pool, LORI_CHARACTER, 530, 400, selected_character,
                           character_select_running);
}

void CharacterSelectScene::start() {
#ifdef LOG
    std::cout << "Starting character select scene..." << std::endl;
#endif

    sound_manager->play_sound(CHARACTER_SELECT_SOUND, 0.5);
    for (auto& selector: selectors) {
        event_loop->mouse.add_on_click_signal_obj(&selector);
    }

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;
    int it = 0;

    // Drop & Rest
    while (game_running && character_select_running) {
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

    std::cout << "is joinning: " << (int)is_joinning << std::endl;
    std::cout << "with id: " << match_selected_id << std::endl;
    if (game_running && !is_joinning) {
        message_handler.create_match(selected_character, selected_map_id, MAX_PLAYERS);
    } else if (game_running && is_joinning) {
        message_handler.join_match(match_selected_id, selected_character);
        is_joinning = false;
    }
}

CharacterSelectScene::~CharacterSelectScene() {
    for (auto& selector: selectors) {
        event_loop->mouse.remove_on_click_signal_obj(&selector);
    }
}
