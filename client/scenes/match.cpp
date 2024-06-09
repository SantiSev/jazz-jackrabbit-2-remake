#include "match.h"

MatchScene::MatchScene(engine::Window& window, EventLoop* event_loop,
                       std::shared_ptr<engine::ResourcePool> resource_pool,
                       std::atomic<bool>& match_running, ClientMessageHandler& message_handler):
        window(window),
        renderer(window.get_renderer()),
        resource_pool(resource_pool),
        event_loop(event_loop),
        message_handler(message_handler),
        game_state_q(message_handler.game_state_q),
        match_running(match_running),
        map(nullptr) {}

void MatchScene::start() {
    init();

    Uint32 frame_start = 0;
    Uint32 frame_time = 0;
    const int frame_delay = 1000 / 60;

    while (match_running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        update_objects(delta_time);

        frame_start = SDL_GetTicks();

        // Draw
        window.clear();
        draw_objects();

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

void MatchScene::init() {
    std::shared_ptr<GameStateDTO> first_state = game_state_q.pop();
    uint8_t num_players = first_state->num_players;
    // uint8_t num_enemies = first_state->num_enemies;
    // uint8_t num_bullets = first_state->num_bullets;
    for (uint8_t i = 0; i < num_players; i++) {
        character_t character = (character_t)first_state->players[i].character;
        auto texture = resource_pool->get_texture(map_character_enum_to_string.at(character));
        auto animations = resource_pool->get_yaml(map_character_enum_to_string.at(character));

        uint8_t state = first_state->players[i].state;
        std::string animation_name = map_states_to_animations.at(state);
        uint16_t x = first_state->players[i].x_pos;
        uint16_t y = first_state->players[i].y_pos;

        engine::AnimatedSprite player_sprite(texture, animations, animation_name, x, y);
        players[first_state->players[i].id] =
                std::make_unique<Player>(std::move(player_sprite), message_handler);
    }
    event_loop->keyboard.add_on_key_down_signal_obj(players.begin()->second.get());
}

void MatchScene::create_objects() {
    // for (auto player: players) {
    //     player->create_objects(renderer, resource_pool);
    // }
}

void MatchScene::update_objects(int delta_time) {
    std::shared_ptr<GameStateDTO> game_state(nullptr);
    game_state_q.try_pop(game_state);

    // update positions
    if (game_state != nullptr) {
        for (uint8_t i = 0; i < game_state->num_players; i++) {
            uint16_t id = game_state->players[i].id;
            uint8_t state = game_state->players[i].state;
            std::string animation_name = map_states_to_animations.at(state);
            uint16_t x = game_state->players[i].x_pos;
            uint16_t y = game_state->players[i].y_pos;

            players.at(id)->set_position(x, y);
            players.at(id)->set_animation(animation_name);
#ifdef LOG_VERBOSE
            std::cout << "Trying to set animation: " << animation_name << std::endl;
#endif
        }
    }

    // update canvas objects
    map->update(delta_time);
    for (auto& player: players) {
        player.second->update(delta_time);
    }
}

void MatchScene::draw_objects() {
    map->draw(renderer);
    for (auto& player: players) {
        player.second->draw(renderer);
    }
}

MatchScene::~MatchScene() {
    // Disconnect from mouse signals
    // for (auto player: players) {
    //     event_loop->keyboard.remove_on_key_down_signal_obj(player);
    //     event_loop->mouse.remove_on_click_signal_obj(player);
    // }
}
