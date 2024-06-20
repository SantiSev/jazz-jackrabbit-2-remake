#include "match_scene.h"

MatchScene::MatchScene(engine::Window& window, EventLoop* event_loop,
                       std::shared_ptr<engine::ResourcePool> resource_pool,
                       std::atomic<bool>& match_running, std::atomic<id_client_t>& id_client,
                       ClientMessageHandler& message_handler, map_list_t map_enum):
        id_client(id_client),
        window(window),
        renderer(window.get_renderer()),
        resource_pool(resource_pool),
        event_loop(event_loop),
        message_handler(message_handler),
        game_state_q(message_handler.game_state_q),
        last_game_state(nullptr),
        match_running(match_running),
        map(std::make_shared<Map>(map_enum, resource_pool)),
        camera(window.get_width(), window.get_height(), map->get_body().w, map->get_body().h),
        player_controller(message_handler) {
    // Blocking call to get first game state
    std::shared_ptr<GameStateDTO> first_state = game_state_q.pop();
    last_game_state = first_state;
    update_objects();
}

void MatchScene::start() {
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
            it = std::round(lost / rate);
        }

        SDL_Delay(rest_time);
        frame_start += rate;
        it++;
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
    // for (uint8_t i = 0; i < game_state->num_items; i++) {
    //     auto item = game_state->items[i];

    //     // If it's a new item create it
    //     items.try_emplace(
    //             item.id,
    //             ItemFactory::create_item(
    //                     resource_pool, static_cast<item_type_t>(item.item_type), item.x_pos,
    //                     item.y_pos));
    //     items[item.id]->set_position(item.x_pos, item.y_pos);
    // }

    last_game_state = game_state;

    if (!game_state) {
        std::cout << "Game state is null" << std::endl;
        return;
    }

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Game State Info:" << std::endl;
    std::cout << "Number of players: " << static_cast<int>(game_state->num_players) << std::endl;
    std::cout << "Number of enemies: " << static_cast<int>(game_state->num_enemies) << std::endl;
    std::cout << "Number of bullets: " << static_cast<int>(game_state->num_bullets) << std::endl;
    std::cout << "Game time (seconds): " << game_state->seconds << std::endl;

    for (uint8_t i = 0; i < game_state->num_players; i++) {
        std::cout << "Player " << static_cast<int>(i) << ": ID " << game_state->players[i].id
                  << ", Character " << static_cast<int>(game_state->players[i].character)
                  << ", State " << static_cast<int>(game_state->players[i].state) << ", Position ("
                  << game_state->players[i].x_pos << ", " << game_state->players[i].y_pos << ")"
                  << std::endl;
    }
    for (uint8_t i = 0; i < game_state->num_enemies; i++) {
        std::cout << "Enemy " << static_cast<int>(i) << ": Type "
                  << static_cast<int>(game_state->enemies[i].character) << ", State "
                  << static_cast<int>(game_state->enemies[i].state) << ", Position ("
                  << game_state->enemies[i].x_pos << ", " << game_state->enemies[i].y_pos << ")"
                  << std::endl;
    }

    for (uint8_t i = 0; i < game_state->num_bullets; i++) {
        std::cout << "Bullet " << static_cast<int>(i) << ": Type ID "
                  << static_cast<int>(game_state->bullets[i].bullet_type) << ", Position ("
                  << game_state->bullets[i].x_pos << ", " << game_state->bullets[i].y_pos << ")"
                  << ", Direction (" << static_cast<int>(game_state->bullets[i].direction) << ")"
                  << std::endl;
    }

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
    // if (last_game_state->num_items < items.size()) {
    //     std::unordered_set<uint16_t> tracked_items;
    //     for (int i = 0; i < last_game_state->num_items; ++i) {
    //         tracked_items.insert(
    //                 last_game_state->items[i].id);  // Assuming Item class has an 'id' attribute
    //     }

    //     for (auto it = items.begin(); it != items.end();) {
    //         // If the item is not in the tracked items set, erase them
    //         if (tracked_items.find(it->first) == tracked_items.end()) {
    //             it = items.erase(it);
    //         } else {
    //             ++it;
    //         }
    //     }
    // }
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
}


MatchScene::~MatchScene() {
    // Disconnect from mouse and keyboard signals
    event_loop->keyboard.remove_on_key_down_signal_obj(&player_controller);
    event_loop->mouse.remove_on_click_signal_obj(&player_controller);
}
