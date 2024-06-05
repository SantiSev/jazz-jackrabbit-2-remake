#include "client.h"

#include "game_objects/GameEnemy.h"
#include "game_objects/GamePlayer.h"

Client::Client(const std::string& host, const std::string& port):
        message_handler(),
        window(800, 600, true, true),
        resource_pool(std::make_shared<engine::ResourcePool>(window.get_renderer())),
        game_running(true),
        menu_running(true),
        match_running(false),
        event_loop(new EventLoop(game_running, menu_running, message_handler)),
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
//     dto.players[0].state, dto.players[0].name); players.push_back(player); for(int i = 1; i <
//     dto.num_enemies; i++) {
//         GameEnemy enemy = GameEnemy(dto.enemies[i].enemy_type, dto.enemies[i].id,
//         dto.enemies[i].state); enemies.push_back(enemy);
//     }
//     this->seconds = dto.seconds;
// }
//
// void check_for_new_players(GameStateDTO& dto, std::vector<GamePlayer>& players) {
//     if (players.size() == dto.num_players) return;
//     for(size_t i = players.size(); i < dto.num_players; i++) {
//         GamePlayer player = GamePlayer(dto.players[i].id, dto.players[i].character,
//         dto.players[i].state, dto.players[i].name); players.push_back(player);
//     }
// }
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
// void update_match(GameStateDTO& dto, std::vector<GamePlayer>& players, std::vector<GameEnemy>&
// enemies) {
//     for(int i = 0; i < dto.num_players; i++) {
//         GamePlayer player = get_player_by_id(dto.players[i].id, players);
//         player.set_health(dto.players[i].health);
//         player.set_points(dto.players[i].points);
//         player.set_state(dto.players[i].state);
//     }
//     int j = 0;
//     for(auto& enemy : enemies) {
//         enemy.set_health(dto.players[j].health);
//         enemy.set_state(dto.players[j].state);
//         j++;
//     }
// }

void Client::start() {
    Menu menu(window, event_loop, resource_pool, game_running, menu_running);

    event_loop->start();

    while (game_running) {
        menu.start();
        if (match_running) {
            // TODO agregar como atributo match la cola game_state_q, para poder pasarle la info de
            // game state. y agregar lo siguiente dentro para ejecutar el mensaje:
            //
            Queue<std::shared_ptr<GameStateDTO>> game_state_q;
            std::shared_ptr<GameStateDTO> game_state;
            game_state_q.try_pop(game_state);


            //             Match match(window, event_loop, resource_pool, game_running,
            //             match_running, game_state_q);
            // match.start();
        }
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
    resource_pool->load_texture(JAZZ);
    resource_pool->load_texture("assets/jazz_test.png");

    // Fonts
    resource_pool->load_font(FONT, FONT_SIZE);
}

Client::~Client() {
    event_loop->stop();
    event_loop->join();
    delete thread_manager;
    delete event_loop;
}
