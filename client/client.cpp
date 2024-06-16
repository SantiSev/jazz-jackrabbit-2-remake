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

void Client::start() {
    MenuScene menu_scene(window, event_loop, resource_pool, game_running, menu_running,
                         message_handler);
    MatchScene match_scene(window, event_loop, resource_pool, match_running, message_handler);
    event_loop->start();

    while (game_running) {
        menu_scene.start();
        if (match_running && map_enum != NO_MAP) {
            match_scene.load_map(map_enum);
            match_scene.start();
        }
        // TODO Level editor
        // if (editor_running) {
        //     editor_scene.start();
        // }
    }
}

void Client::pre_load_resources(std::shared_ptr<engine::ResourcePool>& pool) {
    // Textures
    pool->load_texture(BACKGROUNDS);
    pool->load_texture(map_character_enum_to_string.at(JAZZ_CHARACTER));
    pool->load_texture(map_character_enum_to_string.at(SPAZ_CHARACTER));
    pool->load_texture(map_character_enum_to_string.at(LORI_CHARACTER));
    pool->load_texture(SFX_FILE);
    pool->load_texture(ENEMIES_FILE);
    pool->load_texture(map_list_to_string.at(MAP_1));

    // Fonts
    pool->load_font(FONT, FONT_SIZE);

    // Yaml
    pool->load_yaml(map_character_enum_to_string.at(JAZZ_CHARACTER));
    pool->load_yaml(map_character_enum_to_string.at(SPAZ_CHARACTER));
    pool->load_yaml(map_character_enum_to_string.at(LORI_CHARACTER));
    pool->load_yaml(map_character_enum_to_string.at(MAD_HATTER));
    pool->load_yaml(map_character_enum_to_string.at(LIZARD_GOON));
    pool->load_yaml(SFX_FILE);
    pool->load_yaml(map_list_to_string.at(MAP_1));
}

Client::~Client() {
    event_loop->stop();
    event_loop->join();
    delete thread_manager;
    delete event_loop;
}
