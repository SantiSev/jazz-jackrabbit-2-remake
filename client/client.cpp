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
        message_runner(new MessageRunner(message_handler)),
        thread_manager(new ClientThreadManager(host, port, message_runner->recv_message,
                                               message_handler.send_message)) {
    // Pre-load necessary resources
    pre_load_resources();
    message_runner->start();
}

void Client::start() {
    MenuScene menu_scene(window, event_loop, resource_pool, game_running, menu_running,
                         message_handler);
    event_loop->start();

    while (game_running) {
        menu_scene.start();
        if (match_running && map_enum != NO_MAP) {
            MatchScene match_scene(window, event_loop, resource_pool, match_running, id_client,
                                   message_handler, map_enum);
            match_scene.start();
        }
        // TODO Level editor
        // if (editor_running) {
        //     editor_scene.start();
        // }
    }
}

void Client::pre_load_resources() {
    // Textures
    resource_pool->load_texture(BACKGROUNDS);
    resource_pool->load_texture(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_texture(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_texture(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_texture(SFX_FILE);
    resource_pool->load_texture(ITEMS_FILE);
    resource_pool->load_texture(ENEMIES_FILE);
    resource_pool->load_texture(map_list_to_string.at(MAP_1));

    // Fonts
    resource_pool->load_font(FONT, FONT_SIZE);

    // Yaml
    resource_pool->load_yaml(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(MAD_HATTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LIZARD_GOON));
    resource_pool->load_yaml(SFX_FILE);
    resource_pool->load_yaml(ITEMS_FILE);
    resource_pool->load_yaml(map_list_to_string.at(MAP_1));
}

Client::~Client() {
    message_runner->stop();
    event_loop->stop();
    message_runner->join();
    event_loop->join();
    delete thread_manager;
    delete message_runner;
    delete event_loop;
}
