#include "score_scene.h"

#include <algorithm>

#define LABEL_X 100
#define LABEL_Y 320
#define OFFSET_Y 75
#define LABEL_W 600
#define LABEL_H 50

ScoreScene::ScoreScene(engine::Window& window, EventLoop* event_loop,
                       const std::shared_ptr<engine::ResourcePool>& resource_pool,
                       std::atomic<bool>& menu_running, std::atomic<bool>& scoreboard_running,
                       ClientMessageHandler& message_handler,
                       std::shared_ptr<GameStateDTO>& last_game_state):
        window(window),
        renderer(window.get_renderer()),
        event_loop(event_loop),
        resource_pool(resource_pool),
        background(nullptr),
        game_state(last_game_state),
        labels(),
        menu_running(menu_running),
        scoreboard_running(scoreboard_running) {
    // Create background
    SDL_Rect background_s_rect = {16, 1952, 640, 480};
    SDL_Rect background_d_rect = {0, 0, 800, 600};
    background = new engine::Sprite(resource_pool->get_texture(BACKGROUNDS), background_s_rect,
                                    background_d_rect);

    // Create buttons
    SDL_Rect create_match_button_d_rect = {300, 100, 200, 50};
    auto create_return_button =
            new ReturnMenuButton(renderer, resource_pool, create_match_button_d_rect, menu_running,
                                 scoreboard_running, message_handler);
    buttons.push_back(create_return_button);

    // Create labels
    create_score_labels();
}

void ScoreScene::start() {
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
    while (scoreboard_running) {
        // Draw
        window.clear();
        background->draw(renderer, it);
        for (auto button: buttons) {
            button->draw(renderer, it);
        }
        for (auto label: labels) {
            label->draw(renderer, it);
        }
        window.render();

        frame_end = SDL_GetTicks();
        int rest_time = rate - (frame_end - frame_start);

        if (rest_time < 0) {
            behind = -rest_time;
            rest_time = rate - (behind % rate);
            lost = behind / rate;
            frame_start += lost;
            it = std::round(lost / rate);
        }

        SDL_Delay(rest_time);
        frame_start += rate;
        it++;
    }

    // Disconnect from mouse signals
    for (auto button: buttons) {
        event_loop->mouse.remove_on_click_signal_obj(button);
    }
}

void ScoreScene::create_score_labels() {
    std::vector<PlayerDTO> players;
    if (game_state->num_players == 0) {
        return;
    }
    for (uint8_t i = 0; i < game_state->num_players; i++) {
        players.push_back(game_state->players[i]);
    }

    if (players.size() > 1) {

        std::sort(players.begin(), players.end(),
                  [](const PlayerDTO& a, const PlayerDTO& b) { return a.points > b.points; });
    }

    std::string first_place = "First Place: player " + std::to_string(players[0].id) + " with " +
                              std::to_string(players[0].points) + " points";
    SDL_Rect first_place_d_rect = {LABEL_X, LABEL_Y, LABEL_W, LABEL_H};
    auto score_1 = new engine::Label(resource_pool->get_font(FONT), first_place_d_rect,
                                     {250, 0, 0, 0}, {0, 0, 0, 255}, first_place, renderer);
    labels.push_back(score_1);

    if (players.size() > 1) {
        SDL_Rect second_place_d_rect = {LABEL_X, LABEL_Y + OFFSET_Y, LABEL_W, LABEL_H};
        std::string second_place = "Second Place: player " + std::to_string(players[1].id) +
                                   " with " + std::to_string(players[1].points) + " points";
        auto score_2 = new engine::Label(resource_pool->get_font(FONT), second_place_d_rect,
                                         {250, 0, 0, 0}, {0, 0, 0, 255}, second_place, renderer);
        labels.push_back(score_2);
    }

    if (players.size() > 2) {
        SDL_Rect third_place_d_rect = {LABEL_X, LABEL_Y + 2 * OFFSET_Y, LABEL_W, LABEL_H};
        std::string third_place = "Third Place: player " + std::to_string(players[2].id) +
                                  " with " + std::to_string(players[2].points) + " points";
        auto score_3 = new engine::Label(resource_pool->get_font(FONT), third_place_d_rect,
                                         {250, 0, 0, 0}, {0, 0, 0, 255}, third_place, renderer);
        labels.push_back(score_3);
    }
}

ScoreScene::~ScoreScene() {
    // Free memory
    delete background;
    for (auto button: buttons) {
        delete button;
    }
    for (auto label: labels) {
        delete label;
    }
}
