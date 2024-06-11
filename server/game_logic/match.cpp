#include "match.h"


Match::Match(const map_list_t& map_selected, size_t required_players_setting,
             std::shared_ptr<Queue<std::shared_ptr<Message>>>& lobby_queue):
        online(true),
        event_queue(std::make_shared<Queue<std::shared_ptr<Message>>>()),
        lobby_queue(lobby_queue),
        message_handler(*this),
        players({}),
        enemies({}),
        bullets({}),
        items({}),
        required_players(required_players_setting),
        client_monitor(),
        map(map_selected),
        collision_manager(nullptr) {

    load_enviorment(map_selected);
    load_spawn_points();
    initiate_enemies();
}

void Match::run() {
    try {

        /* while (online && players.size() != required_players) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Match map: " << map << " Waiting for all players to connect to start..."
        << std::endl;
        } */

        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        auto startTime = std::chrono::system_clock::now();
        auto runTime = startTime;

        const double FPSMAX = 1000.0 / 60.0;

        std::cout << "Match map: " << map_list_to_string.at(map) << " Starting..." << std::endl;

        while (online) {
            std::shared_ptr<Message> message;
            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> delta = endTime - startTime;
            startTime = endTime;

            auto frameStart = std::chrono::system_clock::now();

            size_t events = 0;

            while (event_queue->try_pop(message) && events < MAX_EVENTS_PER_LOOP) {
                events++;
                message->run(message_handler);
            }

            collision_manager->update();
            collision_manager->remove_inactive_bodies();

            respawn_enemies();
            respawn_players();
            respawn_items();

            countdown_match(runTime, endTime);

            auto snapshot = create_actual_snapshot();
            auto snapshot_message = std::make_shared<SendGameStateMessage>(snapshot);
            client_monitor.broadcastClients(snapshot_message);

            auto frameEnd = std::chrono::system_clock::now();
            delta = frameEnd - frameStart;

            if (match_has_ended) {
                online = false;
            }

            if (delta.count() < FPSMAX) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(static_cast<int>(FPSMAX - delta.count())));
            }
        }
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

//-------------------- Gameloop Methods ----------------------


void Match::countdown_match(std::chrono::time_point<std::chrono::system_clock>& runTime,
                            const std::chrono::time_point<std::chrono::system_clock>& endTime) {
    if (match_time != 0 && !match_has_ended) {
        if (std::chrono::duration_cast<std::chrono::seconds>(endTime - runTime).count() >= 1) {
            match_time--;
            runTime = endTime;
            size_t minutes = match_time / 60;
            size_t seconds = match_time % 60;
            std::cout << "Time Remaining: " << std::setw(2) << std::setfill('0') << minutes << ":"
                      << std::setw(2) << std::setfill('0') << seconds << std::endl;
        }
    } else {
        if (!match_has_ended) {
            std::cout << "Game Over" << std::endl;
            match_has_ended = true;
        }
    }
}

void Match::run_command(const CommandDTO& dto) {
    std::shared_ptr<Player> player = get_player(dto.id_player);
    if (player) {
        player->execute_command(dto.command);
    }
}

void Match::respawn_players() {
    for (auto& player: players) {
        if (player->try_revive()) {
            player->revive(player.get()->position);
        }
    }
}

void Match::respawn_enemies() {
    for (auto& enemy: enemies) {
        if (enemy->try_revive()) {
            enemy->revive(enemy.get()->spawn_position);
        }
    }
}

void Match::respawn_items() {
    for (auto& item: items) {
        if (item->try_respawn()) {
            item->respawn(item.get()->position);
        }
    }
}

Vector2D Match::select_player_spawn_point() {
    int i = rand() % player_spawn_points.size();
    return player_spawn_points[i];
}


//-------------------- Conection Methods -----------------

void Match::add_player_to_game(const std::string& player_name, const character_t& character,
                               uint16_t client_id) {
    players_connected++;
    Vector2D pos = select_player_spawn_point();
    auto new_player = std::make_shared<Player>(client_id, player_name, character, pos.x, pos.y,
                                               *collision_manager);
    collision_manager->track_dynamic_body(new_player);
    players.push_back(new_player);
}


void Match::add_client_to_match(ServerThreadManager* client, const std::string& player_name,
                                const character_t& character) {
    client_monitor.addClient(client->get_sender_queue());
    client->set_receiver_queue(event_queue);
    clients.push_back(client);
    add_player_to_game(player_name, character, client->get_client_id());
    std::cout << "Player connected: " << player_name << " is playing as "
              << map_character_enum_to_string.at(character) << std::endl;
}


void Match::send_end_message_to_players() {
    auto game_ended_message = std::make_shared<SendFinishMatchMessage>();
    client_monitor.broadcastClients(game_ended_message);
}

bool Match::has_match_ended() const { return match_has_ended; }

void Match::stop() {
    online = false;
    std::cout << "stopping match " << std::endl;
    std::cout << "collision manager cleared" << std::endl;
    //    event_queue->close();
    send_end_message_to_players();
    //    for (auto& client: clients) {
    //        client->get_sender_queue()->close();
    //    }
    client_monitor.remove_all_queues();
    clients.clear();
    std::cout << "clients cleared in match" << std::endl;
}

GameStateDTO Match::create_actual_snapshot() {
    GameStateDTO game_state{};
    game_state.seconds = (uint16_t)match_time % 60;
    game_state.num_players = players.size();
    game_state.num_enemies = enemies.size();
    game_state.num_bullets = bullets.size();

    for (size_t i = 0; i < players.size(); ++i) {
        game_state.players[i].id = players[i]->get_id();
        snprintf(game_state.players[i].name, sizeof(game_state.players[i].name), "%s",
                 players[i]->get_name().c_str());
        game_state.players[i].health = players[i]->get_health();
        game_state.players[i].points = players[i]->get_points();
        game_state.players[i].character = players[i]->get_character();
        game_state.players[i].state = players[i]->get_state();
        game_state.players[i].x_pos = players[i].get()->position.x;
        game_state.players[i].y_pos = players[i].get()->position.y;
        for (size_t j = 0; j < NUM_OF_WEAPONS; ++j) {
            game_state.players[i].weapons[j].ammo = players[i]->get_weapon(j)->get_ammo();
            game_state.players[i].weapons[j].is_empty =
                    players[i]->get_weapon(j)->get_ammo() == 0 ? (uint8_t)1 : (uint8_t)0;
            game_state.players[i].weapons[j].weapon_name =
                    (uint8_t)players[i]->get_weapon(j)->get_weapon_id();
        }
    }
    for (size_t i = 0; i < players.size(); ++i) {
        game_state.players[i].state = enemies[i]->get_state();
        game_state.enemies[i].x_pos = enemies[i]->position.x;
        game_state.enemies[i].y_pos = enemies[i]->position.y;
        game_state.enemies[i].state = enemies[i]->get_state();
    }
    for (size_t i = 0; i < bullets.size(); ++i) {
        game_state.bullets[i].x_pos = bullets[i]->position.x;
        game_state.bullets[i].y_pos = bullets[i]->position.y;
        //        game_state.bullets[i].bullet_type = (uint8_t)bullets[i]->get_bullet_type();
        //        PASAR BULLET ID
    }


    return game_state;
}

//-------------------- Initialization Methods -----------------


void Match::load_enviorment(map_list_t map) {
    // hardcoding for testing purposes
    YAML::Node yaml = YAML::LoadFile("/home/santi/Desktop/Facultad/talller_de_programacion/"
                                     "tp_final/tp-final-Veiga/assets/maps/grass_map.yaml");

    if (yaml.IsNull()) {
        throw std::runtime_error("Error loading yaml file");
    }
    int grid_width = yaml["map_width"].as<int>();
    int grid_height = yaml["map_height"].as<int>();

    if (grid_width <= 0 || grid_height <= 0) {
        throw std::runtime_error("Invalid map size");
    }

    collision_manager = std::make_unique<CollisionManager>(grid_width, grid_height);

    std::cout << "Loading map..." << std::endl;

    for (auto obj: yaml["objects"]) {

        bool collision = obj["collision"].as<bool>();

        if (collision) {

            auto d_rect_list_yaml = obj["d_rect_list"];
            for (auto d_rect_obj: d_rect_list_yaml) {
                auto d_rect_yaml = d_rect_obj["d_rect"];

                auto repeat_h = d_rect_yaml["repeat_h"].as<int>();
                auto repeat_v = d_rect_yaml["repeat_v"].as<int>();

                auto x = d_rect_yaml["x"].as<int>();
                auto y = d_rect_yaml["y"].as<int>();
                auto w = d_rect_yaml["w"].as<int>();
                auto h = d_rect_yaml["h"].as<int>();

                // create boxplatofrm shared pointer
                auto new_box = std::make_shared<BoxPlatform>(x, y, w * repeat_h, h * repeat_v);
                collision_manager->add_object(new_box);
            }
        }
    }
    std::cout << "Map loaded !" << std::endl;
}


void Match::load_spawn_points() {

    //    std::string file_path = map_list_to_string.at(map) + YAML_EXTENSION;
    YAML::Node yaml = YAML::LoadFile("/home/santi/Desktop/Facultad/talller_de_programacion/"
                                     "tp_final/tp-final-Veiga/assets/maps/grass_map.yaml");

    //    YAML::Node yaml = YAML::LoadFile(file_path);
    if (yaml.IsNull()) {
        std::cerr << "Error loading yaml file" << std::endl;
        exit(1);
    }

    for (auto obj: yaml["player_spawnpoints"]) {
        auto x = obj["x"].as<int>();
        auto y = obj["y"].as<int>();
        player_spawn_points.emplace_back(x, y);
    }

    for (auto obj: yaml["enemy_spawnpoints"]) {
        auto x = obj["x"].as<int>();
        auto y = obj["y"].as<int>();
        enemy_spawn_points.emplace_back(x, y);
    }
}


void Match::initiate_enemies() {
    int i = 1;

    if (enemy_spawn_points.empty()) {
        throw std::runtime_error("No enemy spawn points found in map.");
    }

    for (auto& spawn_point: enemy_spawn_points) {

        if (i % 2 == 0) {
            auto lizard_goon = std::make_shared<LizardGoon>(i, spawn_point.x, spawn_point.y);
            collision_manager->track_dynamic_body(lizard_goon);
            enemies.emplace_back(lizard_goon);
        } else {
            auto mad_hatter = std::make_shared<MadHatter>(i, spawn_point.x, spawn_point.y);
            collision_manager->track_dynamic_body(mad_hatter);
            enemies.emplace_back(mad_hatter);
        }
        i++;
    }
}


ServerThreadManager& Match::get_client_by_id(id_client_t id_client) {
    auto it =
            std::find_if(clients.begin(), clients.end(), [id_client](ServerThreadManager* client) {
                return client->get_client_id() == id_client;
            });

    if (it != clients.end()) {
        return **it;  // Dereferenciamos el iterador y el puntero
    } else {
        throw std::runtime_error("Client with the given ID not found in match.");
    }
}


void Match::delete_disconnected_player(id_client_t id_client) {
    for (auto player = players.begin(); player != players.end(); ++player) {
        if (id_client == (*player)->get_id()) {
            CloseConnectionDTO dto{id_client};
            client_monitor.removeQueue(get_client_by_id(id_client).get_sender_queue());
            auto message = std::make_shared<CloseConnectionMessage>(dto);
            lobby_queue->try_push(message);
            collision_manager->remove_object(*player);
            players.erase(player);
            erase_client_from_list(id_client);
            std::cout << "Player " << id_client << " disconnected from match " << std::endl;
            break;
        }
    }
}

void Match::erase_client_from_list(id_client_t id_client) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->get_client_id() == id_client) {
            clients.erase(it);
            break;
        }
    }
}

//-------------------- Getter Methods -----------------

size_t Match::get_num_players() { return players.size(); }

map_list_t Match::get_map() const { return map; }

size_t Match::get_max_players() const { return required_players; }

std::shared_ptr<Player> Match::get_player(size_t id) {
    auto it = std::find_if(
            players.begin(), players.end(),
            [id](const std::shared_ptr<Player>& player) { return player->get_id() == id; });
    if (it != players.end()) {
        return *it;
    } else {
        throw std::runtime_error("Player with the given ID not found");
    }
}

std::vector<size_t> Match::get_clients_ids() {
    std::vector<size_t> ids;
    std::transform(clients.begin(), clients.end(), std::back_inserter(ids),
                   [](auto& client) { return client->get_client_id(); });
    return ids;
}
