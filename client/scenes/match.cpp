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
        map(nullptr),
        player_controller(message_handler) {}

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
        auto player = first_state->players[i];
        create_character(player.id, (character_t)player.character, player.state, player.x_pos,
                         player.y_pos);
    }
    // for (uint8_t i = 0; i < num_enemies; i++) {
    //     auto enemy = first_state->enemies[i];
    //     create_character(enemy.id, (character_t)enemy.character, enemy.state, enemy.x_pos,
    //                      enemy.y_pos);
    // }

    // TODO Create bullets // create_bullet(player.id, COMMON_BULLET, player.x_pos, player.y_pos,
    // 0);

    // Connect player controler to keyboard and mouse signals
    event_loop->keyboard.add_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.add_on_click_signal_obj(&player_controller);
}

void MatchScene::create_character(uint16_t id, character_t character, uint8_t state, uint16_t x,
                                  uint16_t y) {
    animated_objects[id] = CharacterFactory::create_character(
            resource_pool, character, map_states_to_animations.at(state), x, y);
}

void MatchScene::create_bullet(uint16_t id, uint8_t bullet_type, uint16_t x, uint16_t y,
                               uint8_t direction) {
    animated_objects[id] =
            BulletFactory::create_bullet(resource_pool, bullet_type, direction, x, y);
}

void MatchScene::update_objects(int delta_time) {
    std::shared_ptr<GameStateDTO> game_state(nullptr);
    game_state_q.try_pop(game_state);

    // update positions
    if (game_state != nullptr) {
        for (uint8_t i = 0; i < game_state->num_players; i++) {
            auto player = game_state->players[i];

            if (animated_objects.find(player.id) == animated_objects.end()) {
                create_character(player.id, (character_t)player.character, player.state,
                                 player.x_pos, player.y_pos);
            }

            animated_objects.at(player.id)->set_position(player.x_pos, player.y_pos);
            animated_objects.at(player.id)->set_animation(
                    map_states_to_animations.at(player.state));
#ifdef LOG_VERBOSE
            std::cout << "Trying to set animation: " << map_states_to_animations.at(player.state)
                      << std::endl;
#endif
        }

        // for (uint8_t i = 0; i < game_state->num_enemies; i++) {
        //     auto enemy = game_state->enemies[i];

        //     if (animated_objects.find(enemy.id) == animated_objects.end()) {
        //         create_character(enemy.id, (character_t)enemy.character, enemy.state,
        //         enemy.x_pos,
        //                          enemy.y_pos);
        //     }

        //     animated_objects.at(enemy.id)->set_position(enemy.x_pos, enemy.y_pos);
        //     animated_objects.at(enemy.id)->set_animation(map_states_to_animations.at(enemy.state));
        // }

        // TODO Create bullets
    }

    // update canvas objects
    map->update(delta_time);
    for (auto& obj: animated_objects) {
        obj.second->update(delta_time);
    }
}

void MatchScene::draw_objects() {
    map->draw(renderer);
    for (auto& obj: animated_objects) {
        obj.second->draw(renderer);
    }
}

MatchScene::~MatchScene() {
    // Disconnect from mouse and keyboard signals
    event_loop->keyboard.remove_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.remove_on_click_signal_obj(&player_controller);

    // for (auto player: players) {
    //     event_loop->keyboard.remove_on_key_down_signal_obj(player);
    //     event_loop->mouse.remove_on_click_signal_obj(player);
    // }
}
