#include "match_select_scene.h"


#define Y_BUTTON_START 200
#define BUTTON_MARGIN 10
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 25

MatchSelectScene::MatchSelectScene(engine::Window& window, EventLoop* event_loop,
                                   std::shared_ptr<engine::ResourcePool> resource_pool,
                                   std::shared_ptr<engine::SoundManager> sound_manager,
                                   std::atomic<bool>& game_running, std::atomic<bool>& menu_running,
                                   std::atomic<bool>& match_select_running,
                                   ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        sound_manager(sound_manager),
        background(std::make_unique<MainScreenBackground>(*resource_pool)),
        game_running(game_running),
        menu_running(menu_running),
        match_select_running(match_select_running),
        character_select_running(false),
        match_requested(false),
        message_handler(message_handler),
        selected_id(0) {

    create_buttons();
}

void MatchSelectScene::start() {
    CharacterSelectScene character_select_scene(window, event_loop, resource_pool, sound_manager,
                                                game_running, character_select_running,
                                                message_handler);
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
    while (game_running && match_select_running) {
        //        if (map_select_running) {
        //            // Disconnect from mouse signals
        //            for (auto button: buttons) {
        //                event_loop->mouse.remove_on_click_signal_obj(button);
        //            }
        //            map_select_scene.start();
        //        }
        if (match_requested) {
            show_matches();
            match_requested = false;
        }

        if (character_select_running) {
            //            character_select_scene.start(map_select_scene.selected_map_id); cambiar a
            //            mapa seleccionado
        }
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
            it += std::floor(lost / rate);
        }

        SDL_Delay(rest_time);
        frame_start += rate;
        it++;
    }
}

void MatchSelectScene::create_buttons() {

    int y_start = Y_BUTTON_START;
    int w = BUTTON_WIDTH;
    int h = BUTTON_HEIGHT;

    // Create buttons
    SDL_Rect receive_matches_button_d_rect = {100, y_start, w, h};
    ReceiveMatchesButton* receive_matches_button =
            new ReceiveMatchesButton(renderer, resource_pool, message_handler, game_running,
                                     match_select_running, receive_matches_button_d_rect);


    //    SDL_Rect join_match_button_d_rect = {0, y_start, w, h};
    //    JoinMatchButton* join_match_button =
    //            new JoinMatchButton(renderer, resource_pool, join_match_button_d_rect,
    //            message_handler);
    //    y_start += h + BUTTON_MARGIN;
    //
    //    SDL_Rect quit_button_d_rect = {0, y_start, w, h};
    //    QuitButton* quit_button = new QuitButton(renderer, resource_pool, quit_button_d_rect,
    //                                             game_running, menu_running, message_handler);

    // Add buttons to list
    buttons.push_back(receive_matches_button);


    // Center buttons
    for (auto button: buttons) {
        button->center_x(0, window.get_width());
    }
}

void MatchSelectScene::show_matches() {
    std::shared_ptr<MatchInfoDTO> match_info = nullptr;
    message_handler.match_select_q.try_pop(match_info);
    if (match_info) {
        create_match_buttons(match_info);
    }
    match_requested = false;
}

MatchSelectScene::~MatchSelectScene() {
    // Free memory
    for (auto button: buttons) {
        delete button;
    }
}

void MatchSelectScene::create_match_buttons(std::shared_ptr<MatchInfoDTO> dto) {
    int y_start = Y_BUTTON_START;
    int w = BUTTON_WIDTH;
    int h = BUTTON_HEIGHT;

    int num_matches = dto->num_games;

    for (int i = 0; i < num_matches; i++) {
        std::string label_info = "Match id :" + std::to_string(dto->active_games[i].map_id) + " " +
                                 std::to_string(dto->active_games[i].players_ingame) + " / " +
                                 std::to_string(dto->active_games[i].players_max);
        uint16_t id = dto->active_games[i].match_id;
        SDL_Rect match_button_d_rect = {0, y_start, w, h};
        MatchSelectorButton* match_button = new MatchSelectorButton(
                renderer, resource_pool, match_button_d_rect, match_select_running,
                character_select_running, label_info, selected_id, id);
        y_start += h + BUTTON_MARGIN;
        buttons.push_back(match_button);
    }
}
