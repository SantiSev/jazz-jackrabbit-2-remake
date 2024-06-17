#include "match_scene.h"

MatchScene::MatchScene(engine::Window& window, EventLoop* event_loop,
                       std::shared_ptr<engine::ResourcePool> resource_pool,
                       std::atomic<bool>& match_running, std::atomic<id_client_t>& id_client,
                       ClientMessageHandler& message_handler):
        id_client(id_client),
        window(window),
        renderer(window.get_renderer()),
        resource_pool(resource_pool),
        event_loop(event_loop),
        message_handler(message_handler),
        game_state_q(message_handler.game_state_q),
        match_running(match_running),
        camera(window.get_width(), window.get_height(), 1280, 1000),
        map(nullptr),
        player_controller(message_handler) {}

void MatchScene::start() {
    init();

    const Uint32 rate = 1000 / 60;

    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_end;
    Uint32 behind;
    Uint32 lost;
    int it = 0;

    // Drop & Rest
    while (match_running) {
        // Draw
        window.clear();
        draw_objects(it);
        window.render();
        update_objects(it);

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
}


void MatchScene::load_map(const map_list_t& map_enum) {
    map = std::make_shared<Map>(map_enum, resource_pool);
}


void MatchScene::init() {
    // Blocking call to get first game state
    std::shared_ptr<GameStateDTO> first_state = game_state_q.pop();
    last_game_state = first_state;

    for (uint8_t i = 0; i < first_state->num_players; i++) {
        auto player = first_state->players[i];
        players[player.id] = CharacterFactory::create_character(
                resource_pool, (character_t)player.character,
                map_states_to_animations.at(player.state), player.x_pos, player.y_pos);

        if (player.id == id_client) {
            camera.recenter(players.at(player.id)->get_body());
        }
    }
    for (uint8_t i = 0; i < first_state->num_enemies; i++) {
        auto enemy = first_state->enemies[i];
        enemies[enemy.id] = CharacterFactory::create_character(
                resource_pool, (character_t)enemy.character,
                map_states_to_animations.at(enemy.state), enemy.x_pos, enemy.y_pos);
    }
    for (uint8_t i = 0; i < first_state->num_bullets; i++) {
        auto bullet = first_state->bullets[i];
        bullets[bullet.id] =
                BulletFactory::create_bullet(resource_pool, (bullet_type_t)bullet.bullet_type,
                                             bullet.direction, bullet.x_pos, bullet.y_pos);
    }

    // Connect player controler to keyboard and mouse signals
    event_loop->keyboard.add_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.add_on_click_signal_obj(&player_controller);
}


void MatchScene::update_objects(int delta_time) {
    std::shared_ptr<GameStateDTO> game_state(nullptr);
    while (game_state_q.try_pop(game_state)) {}  // get last game state

    // update positions
    if (!game_state) {
        game_state = last_game_state;
    }

    for (uint8_t i = 0; i < game_state->num_players; i++) {
        auto player = game_state->players[i];

        // If it's a new player create it
        players.try_emplace(
                player.id,
                CharacterFactory::create_character(
                        resource_pool, static_cast<character_t>(player.character),
                        map_states_to_animations.at(player.state), player.x_pos, player.y_pos));
        players[player.id]->set_position(player.x_pos, player.y_pos);
        if (player.id == id_client) {
            camera.recenter(players[player.id]->get_body());
        }
        players[player.id]->set_animation(map_states_to_animations.at(player.state));
    }

    for (uint8_t i = 0; i < game_state->num_enemies; i++) {
        auto enemy = game_state->enemies[i];
        // If it's a new enemy create it
        enemies.try_emplace(
                enemy.id,
                CharacterFactory::create_character(
                        resource_pool, static_cast<character_t>(enemy.character),
                        map_states_to_animations.at(enemy.state), enemy.x_pos, enemy.y_pos));
        enemies[enemy.id]->set_position(enemy.x_pos, enemy.y_pos);
        enemies[enemy.id]->set_animation(map_states_to_animations.at(enemy.state));
    }

    for (uint8_t i = 0; i < game_state->num_bullets; i++) {
        auto bullet = game_state->bullets[i];

        // If it's a new bullet create it
        bullets.try_emplace(bullet.id,
                            BulletFactory::create_bullet(
                                    resource_pool, static_cast<bullet_type_t>(bullet.bullet_type),
                                    bullet.direction, bullet.x_pos, bullet.y_pos));
        bullets[bullet.id]->set_position(bullet.x_pos, bullet.y_pos);
    }

    // TODO Remove objects that are not in the game state
    last_game_state = game_state;
}


void MatchScene::draw_objects(int it) {
    map->draw_in_camera(renderer, camera.get_body(), it);

    for (auto& player: players) {
        camera.adjust_relative_position(*player.second);
        player.second->draw(renderer, it);
    }
    for (auto& enemy: enemies) {
        camera.adjust_relative_position(*enemy.second);
        enemy.second->draw(renderer, it);
    }
    for (auto& bullet: bullets) {
        camera.adjust_relative_position(*bullet.second);
        bullet.second->draw(renderer, it);
    }
}


MatchScene::~MatchScene() {
    // Disconnect from mouse and keyboard signals
    event_loop->keyboard.remove_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.remove_on_click_signal_obj(&player_controller);
}
