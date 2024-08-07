#include "client.h"

Client::Client(const std::string& host, const std::string& port):
        window(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, true, true),
        resource_pool(std::make_shared<engine::ResourcePool>(window.get_renderer())),
        game_running(true),
        menu_running(true),
        match_running(false),
        editor_running(false),
        map_enum(0),
        id_client(0),
        message_handler(*this),
        event_loop(new EventLoop(game_running, menu_running, match_running, editor_running,
                                 message_handler)),
        message_runner(new MessageRunner(message_handler)),
        thread_manager(new ClientThreadManager(host, port, message_runner->recv_message,
                                               message_handler.send_message)),
        sound_manager(std::make_shared<engine::SoundManager>(resource_pool)) {
    // Pre-load necessary resources
    pre_load_resources();
    message_runner->start();
}

void Client::start() {
#ifdef LOG
    std::cout << "Starting client..." << std::endl;
#endif
    MenuScene menu_scene(window, event_loop, resource_pool, sound_manager, game_running,
                         menu_running, editor_running, message_handler);
    event_loop->start();

    sound_manager->play_sound(BACKGROUND, 0.15);

    while (game_running) {
        menu_scene.start();
        if (match_running && map_enum != 0) {
            MatchScene match_scene(window, event_loop, resource_pool, sound_manager,
                                   message_handler, id_client, match_running, menu_running,
                                   map_enum);
            match_scene.start();
        }
        if (editor_running) {
            EditorScene editor_scene(window, event_loop, resource_pool, menu_running,
                                     editor_running, message_handler);
            editor_scene.start();
        }
    }
}

void Client::pre_load_resources() {
#ifdef LOG
    std::cout << "Pre-loading resources..." << std::endl;
#endif

    // Textures
    resource_pool->load_texture(BACKGROUNDS_FILE);
    resource_pool->load_texture(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_texture(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_texture(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_texture(SFX_FILE);
    resource_pool->load_texture(ITEMS_FILE);
    resource_pool->load_texture(ENEMIES_FILE);
    resource_pool->load_texture(EDITOR_FILE);
    resource_pool->load_texture(CHARACTER_SELECT_FILE);
    resource_pool->load_texture(ICONS_FILE);

    // Fonts
    resource_pool->load_font(FONT, FONT_SIZE);

    // Yaml
    resource_pool->load_yaml(BACKGROUNDS_FILE);
    resource_pool->load_yaml(map_character_enum_to_string.at(JAZZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(SPAZ_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LORI_CHARACTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(MAD_HATTER));
    resource_pool->load_yaml(map_character_enum_to_string.at(LIZARD_GOON));
    resource_pool->load_yaml(SFX_FILE);
    resource_pool->load_yaml(ITEMS_FILE);
    resource_pool->load_yaml(EDITOR_FILE);
    resource_pool->load_yaml(MAPS_FILE);
    resource_pool->load_yaml(CHARACTER_SELECT_FILE);
    resource_pool->load_yaml(ICONS_FILE);

    // Sounds
    resource_pool->load_music(sound_to_string.at(BACKGROUND));
    resource_pool->load_sound_effect(sound_to_string.at(SHOOT_SOUND));
    resource_pool->load_sound_effect(sound_to_string.at(CHARACTER_SELECT_SOUND));

    // Config
    resource_pool->load_config(CONFIG_FILE);

#ifdef LOG
    std::cout << "Resources pre-loaded" << std::endl;
#endif
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
