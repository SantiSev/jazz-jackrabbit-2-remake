#include "client.h"

Client::Client(const std::string& host, const std::string& port):
        window(800, 600, true, true),
        resource_pool(std::make_shared<engine::ResourcePool>(window.get_renderer())),
        game_running(true),
        menu_running(true),
        match_running(false),
        map_enum(NO_MAP),
        id_client(0),
        message_handler(*this),
        event_loop(new EventLoop(game_running, menu_running, match_running, message_handler)),
        thread_manager(new ClientThreadManager(host, port, event_loop->recv_message,
                                               message_handler.send_message)) {
    // Pre-load necessary resources
    pre_load_resources(resource_pool);
}

// le pasas los atributos lista de players y enemies o despues reemplazas dentro de la funcion
// directamente los atributos. tambien falta agregarle delante de cada nombre de funcion el Match::

// void initiate_match(GameStateDTO& dto, std::vector<GamePlayer>& players, std::vector<GameEnemy>&
// enemies) {
//     GamePlayer player = GamePlayer(dto.players[0].id, dto.players[0].character,
//     dto.players[0].state, dto.players[0].name);
//
//     players.push_back(player); for(int i = 1; i < dto.num_enemies; i++) {
//         GameEnemy enemy = GameEnemy(dto.enemies[i].enemy_type,dto.enemies[i].state);
//         enemies.push_back(enemy);
//     }
////     this->seconds = dto.seconds;
// }
//
// void check_for_new_bullets(GameStateDTO& dto, std::vector<GameBullets>& bullets) {
//    if (bullets.size() == dto.num_players) return;
//    for(size_t i = bullets.size(); i < dto.num_players; i++) {
//        GameBullets bullet = GameBullets(dto.bullets[i].x_pos, dto.bullets[i].y_pos,
//        dto.bullets[i].bullet_type); bullets.push_back(bullet);
//    }
//}
//
// GamePlayer get_player_by_id(uint8_t id, std::vector<GamePlayer>& players) {
//     for(auto& player : players) {
//         if(player.get_id() == id) {
//             return player;
//         }
//     }
//     throw std::runtime_error("Player with the given ID not found");
// }
//
// bool playerExistsInMatch(const GamePlayer& player, const GameStateDTO& gameState) {
//    for (int i = 0; i < gameState.num_players; ++i) {
//        if (gameState.players[i].id == player.get_id()) {
//            return true;
//        }
//    }
//    return false;
//}
//
// void removeDisconnectedPlayers(std::vector<GamePlayer>& currentPlayers, const GameStateDTO&
// gameState) {
//    auto newEnd = std::remove_if(currentPlayers.begin(), currentPlayers.end(),
//                                 [&gameState](const GamePlayer& player) {
//                                     return !playerExistsInMatch(player, gameState);
//                                 });
//    if (newEnd != currentPlayers.end()) {
//        std::cout << "Removing disconnected players..." << std::endl;
//        currentPlayers.erase(newEnd, currentPlayers.end());
//    }
//}
//
// void check_for_new_players(GameStateDTO& dto, std::vector<GamePlayer>& players) {
//    if (players.size() == dto.num_players) return;
//    for(size_t i = players.size(); i < dto.num_players; i++) {
//        GamePlayer player = GamePlayer(dto.players[i].id, dto.players[i].character,
//                                       dto.players[i].state, dto.players[i].name);
//        player.set_position(dto.players[i].x_pos, dto.players[i].y_pos);
//        players.push_back(player);
//    }
//}
//
// void update_match(GameStateDTO& dto, std::vector<GamePlayer>& players, std::vector<GameEnemy>&
// enemies) {
//     for(int i = 0; i < dto.num_players; i++) {
//         GamePlayer player = get_player_by_id(dto.players[i].id, players);
//         player.set_health(dto.players[i].health);
//         player.set_points(dto.players[i].points);
//         player.set_state(dto.players[i].state);
//         player.set_position(dto.players[i].x_pos, dto.players[i].y_pos);
//     }
//     int j = 0;
//     for(auto& enemy : enemies) {
//         enemy.set_health(dto.players[j].health);
//         enemy.set_state(dto.players[j].state);
//         enemy.set_position(dto.players[j].x_pos, dto.players[j].y_pos);
//         j++;
//     }
// }

void Client::start() {
    MenuScene menu_scene(window, event_loop, resource_pool, game_running, menu_running,
                         message_handler);
    MatchScene match_scene(window, event_loop, resource_pool, match_running, message_handler);
    event_loop->start();

    while (game_running) {
        menu_scene.start();
        if (match_running && map_enum != NO_MAP) {
            // match_scene.load_map(map_enum);
            match_scene.load_map(map_enum);
            match_scene.start();
        }
        // if (editor_running) {
        //     editor_scene.start();
        // }
    }

    //    std::list<engine::CanvasObject*> objects;
    //
    //    SDL_Rect rect = {19, 32, 61, 59};
    //    SDL_Rect d_rect = {0, 0, 450, 590};
    //    engine::AnimatedSprite sprite(resource_pool.get_texture("assets/jazz_test.png"), rect,
    //    d_rect,
    //                                  6, 8);
    //    Player player(std::move(sprite));
    //    objects.push_back(&player);
    //
    //    event_loop->keyboard.add_on_key_down_signal_obj(&player);
    //    event_loop->mouse.add_on_click_signal_obj(&player);
    //
    //    event_loop->start();
    //
    //    Uint32 frame_start = 0;
    //    Uint32 frame_time = 0;
    //    const int frame_delay = 1000 / 60;
    //
    //    while (game_running) {
    //        // Updates
    //        int delta_time = SDL_GetTicks() - frame_start;
    //        for (auto object: objects) {
    //            object->update(delta_time);
    //        }
    //
    //        frame_start = SDL_GetTicks();
    //
    //        // Draw
    //        window.clear();
    //        for (auto object: objects) {
    //            object->draw(renderer);
    //        }
    //        window.render();
    //
    //        frame_time = SDL_GetTicks() - frame_start;
    //        if (frame_delay > frame_time) {  // Delay to achieve desired fps
    //            SDL_Delay(frame_delay - frame_time);
    //        }
    //    }
}

void Client::pre_load_resources(std::shared_ptr<engine::ResourcePool>& resource_pool) {
    // Textures
    resource_pool->load_texture(BACKGROUNDS);
    resource_pool->load_texture(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_texture(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_texture(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_texture(map_list_to_string.at(MAP_1));

    // Fonts
    resource_pool->load_font(FONT, FONT_SIZE);

    // Yaml
    resource_pool->load_yaml(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_yaml(map_list_to_string.at(MAP_1));
}

Client::~Client() {
    event_loop->stop();
    event_loop->join();
    delete thread_manager;
    delete event_loop;
}
