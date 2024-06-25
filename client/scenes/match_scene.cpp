#include "match_scene.h"

MatchScene::MatchScene(engine::Window& window, EventLoop* event_loop,
                       const std::shared_ptr<engine::ResourcePool>& resource_pool,
                       std::shared_ptr<engine::SoundManager> sound_manager,
                       ClientMessageHandler& message_handler, std::atomic<id_client_t>& id_client,
                       std::atomic<bool>& match_running, std::atomic<bool>& menu_running,
                       uint16_t map_id):
        id_client(id_client),
        window(window),
        renderer(window.get_renderer()),
        resource_pool(resource_pool),
        sound_manager(sound_manager),
        event_loop(event_loop),
        message_handler(message_handler),
        game_state_q(message_handler.game_state_q),
        last_game_state(nullptr),
        match_running(match_running),
        menu_running(menu_running),
        map(std::make_shared<Map>(map_id, resource_pool)),
        hud(nullptr),
        camera(window.get_width(), window.get_height(), 0, map->get_body().w, 0, map->get_body().h),
        player_controller(message_handler) {
#ifdef LOG
    std::cout << "Constructing match scene..." << std::endl;
#endif
    // Blocking call to get first game state
    std::shared_ptr<GameStateDTO> first_state = game_state_q.pop();
    last_game_state = first_state;
    update_objects();
}

void MatchScene::start() {
#ifdef LOG
    std::cout << "Starting match scene..." << std::endl;
#endif
    // Connect player controler to keyboard and mouse signals
    event_loop->keyboard.add_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.add_on_click_signal_obj(&player_controller);

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
        update_objects();

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
    if (menu_running) {
        std::atomic<bool> scoreboard_running = true;
        ScoreScene score_scene(window, event_loop, resource_pool, menu_running, scoreboard_running,
                               message_handler, last_game_state, id_client);
        score_scene.start();
    }
}

void MatchScene::update_objects() {
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
            if (!hud) {
                hud = std::make_unique<IngameHud>(renderer, resource_pool, player,
                                                  static_cast<uint16_t>(game_state->seconds));
            }
            hud->update(player, game_state->seconds);
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
        auto [it, inserted] = bullets.try_emplace(
                bullet.id, BulletFactory::create_bullet(
                                   resource_pool, static_cast<bullet_type_t>(bullet.bullet_type),
                                   bullet.direction, bullet.x_pos, bullet.y_pos));
        if (inserted) {
            std::cout << "Shoot sound" << std::endl;
            sound_manager->play_sound(SHOOT_SOUND, 0.25);
        }
        bullets[bullet.id]->set_position(bullet.x_pos, bullet.y_pos);

    for (uint8_t i = 0; i < game_state->num_items; i++) {
        auto item = game_state->items[i];

        // If it's a new item create it
        items.try_emplace(item.id,
                          ItemFactory::create_item(resource_pool, static_cast<item_t>(item.type),
                                                   item.x_pos, item.y_pos));
        items[item.id]->set_position(item.x_pos, item.y_pos);
    }

    last_game_state = game_state;

    destroy_untracked_objects();
}

void MatchScene::destroy_untracked_objects() {
    // Destroy untracked players
    if (last_game_state->num_players < players.size()) {
        std::unordered_set<uint16_t> tracked_players;
        for (int i = 0; i < last_game_state->num_players; ++i) {
            tracked_players.insert(
                    last_game_state->players[i].id);  // Assuming Player class has an 'id' attribute
        }

        for (auto it = players.begin(); it != players.end();) {
            // If the player is not in the tracked players set, erase them
            if (tracked_players.find(it->first) == tracked_players.end()) {
                it = players.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Destroy untracked enemies
    if (last_game_state->num_enemies < enemies.size()) {
        std::unordered_set<uint16_t> tracked_enemies;
        for (int i = 0; i < last_game_state->num_enemies; ++i) {
            tracked_enemies.insert(
                    last_game_state->enemies[i].id);  // Assuming Enemy class has an 'id' attribute
        }

        for (auto it = enemies.begin(); it != enemies.end();) {
            // If the enemy is not in the tracked enemies set, erase them
            if (tracked_enemies.find(it->first) == tracked_enemies.end()) {
                it = enemies.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Destroy untracked bullets
    if (last_game_state->num_bullets < bullets.size()) {
        std::unordered_set<uint16_t> tracked_bullets;
        for (int i = 0; i < last_game_state->num_bullets; ++i) {
            tracked_bullets.insert(
                    last_game_state->bullets[i].id);  // Assuming Bullet class has an 'id' attribute
        }
        for (auto it = bullets.begin(); it != bullets.end();) {
            // If the bullet is not in the tracked bullets set, erase them
            if (tracked_bullets.find(it->first) == tracked_bullets.end()) {
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Destroy untracked items
    if (last_game_state->num_items < items.size()) {
        std::unordered_set<uint16_t> tracked_items;
        for (int i = 0; i < last_game_state->num_items; ++i) {
            tracked_items.insert(
                    last_game_state->items[i].id);  // Assuming Item class has an 'id' attribute
        }

        for (auto it = items.begin(); it != items.end();) {
            // If the item is not in the tracked items set, erase them
            if (tracked_items.find(it->first) == tracked_items.end()) {
                it = items.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void MatchScene::draw_objects(int it) {
    map->draw_in_camera(renderer, camera, it);

    for (auto& player: players) {
        bool is_visible = camera.adjust_relative_position(*player.second);
        if (is_visible) {
            player.second->draw(renderer, it);
        }
    }
    for (auto& enemy: enemies) {
        bool is_visible = camera.adjust_relative_position(*enemy.second);
        if (is_visible) {
            enemy.second->draw(renderer, it);
        }
    }
    for (auto& bullet: bullets) {
        bool is_visible = camera.adjust_relative_position(*bullet.second);
        if (is_visible) {
            bullet.second->draw(renderer, it);
        }
    }
    for (auto& item: items) {
        bool is_visible = camera.adjust_relative_position(*item.second);
        if (is_visible) {
            item.second->draw(renderer, it);
        }
    }

    hud->draw(renderer, it);
}


MatchScene::~MatchScene() {
    // Disconnect from mouse and keyboard signals
    event_loop->keyboard.remove_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.remove_on_click_signal_obj(&player_controller);
}
