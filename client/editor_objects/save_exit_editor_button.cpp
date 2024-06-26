#include "save_exit_editor_button.h"

SaveExitEditorButton::SaveExitEditorButton(SDL_Renderer* renderer,
                                           std::shared_ptr<engine::ResourcePool> resource_pool,
                                           SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                                           std::atomic<bool>& editor_running,
                                           TileManager& tile_manager):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Save and Exit", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        resource_pool(resource_pool),
        menu_running(menu_running),
        editor_running(editor_running),
        tile_manager(tile_manager) {}

void SaveExitEditorButton::on_click() {
#ifdef LOG
    std::cout << "Clicked save and exit button." << std::endl;
#endif
    save_map();
    menu_running.store(true);
    editor_running.store(false);
}

void SaveExitEditorButton::save_map() {
    const auto& map = tile_manager.get_tiles();
    std::list<SDL_Rect> player_spawnpoints;
    std::list<SDL_Rect> enemy_spawnpoints;
    std::list<SDL_Rect> item_spawnpoints;

    // Create YAML emitter
    YAML::Emitter out;
    out << YAML::BeginMap;

    // Emit YAML for the map
    add_metadata(out);

    out << YAML::Key << "objects" << YAML::Value << YAML::BeginSeq;

    // Iterate through tiles and export each EditorTile
    for (const auto& pair: map) {
        const auto& tile = pair.second;

        // Get s_rect data
        TileType type = tile->type;
        auto& s_rect = tile->get_s_rect();
        auto d_rect = tile->get_d_rect();

        switch (type) {
            case PLAYER_SPAWN:
                player_spawnpoints.push_back(d_rect);
                continue;
                break;
            case ENEMY_SPAWN:
                enemy_spawnpoints.push_back(d_rect);
                continue;
                break;
            case ITEM_SPAWN:
                item_spawnpoints.push_back(d_rect);
                continue;
                break;
            case NULL_TILE:
                continue;
            default:
                break;
        }

        // Emit YAML for the current tile
        out << YAML::BeginMap;
        out << YAML::Key << "collision" << YAML::Value << true;  // Example value for collision
        out << YAML::Key << "s_rect" << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << s_rect.x;
        out << YAML::Key << "y" << YAML::Value << s_rect.y;
        out << YAML::Key << "w" << YAML::Value << s_rect.w;
        out << YAML::Key << "h" << YAML::Value << s_rect.h;
        out << YAML::EndMap;
        out << YAML::Key << "d_rect_list" << YAML::Value << YAML::BeginSeq;
        out << YAML::BeginMap;
        out << YAML::Key << "d_rect" << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "repeat_h" << YAML::Value << 1;
        out << YAML::Key << "repeat_v" << YAML::Value << 1;
        out << YAML::Key << "x" << YAML::Value << d_rect.x;
        out << YAML::Key << "y" << YAML::Value << d_rect.y;
        out << YAML::Key << "w" << YAML::Value << d_rect.w;
        out << YAML::Key << "h" << YAML::Value << d_rect.h;
        out << YAML::EndMap;
        out << YAML::EndMap;
        out << YAML::EndSeq;
        out << YAML::EndMap;
    }

    // End objects map
    out << YAML::EndSeq;

    add_spawns(out, PLAYER_SPAWN, player_spawnpoints);
    add_spawns(out, ENEMY_SPAWN, enemy_spawnpoints);
    add_spawns(out, ITEM_SPAWN, item_spawnpoints);

    // End main map
    out << YAML::EndMap;

    // Write YAML to file
    std::ofstream fout("new_map.yaml");
    fout << out.c_str();
    fout.close();

    std::cout << "Data saved to tiles.yaml successfully." << std::endl;
}

void SaveExitEditorButton::add_spawns(YAML::Emitter& out, TileType type,
                                      std::list<SDL_Rect> d_rects) {
    std::string seq_name;
    int min_spawnpoints;
    switch (type) {
        case PLAYER_SPAWN:
            seq_name = "player_spawnpoints";
            min_spawnpoints = MAX_PLAYERS;
            break;
        case ENEMY_SPAWN:
            seq_name = "enemy_spawnpoints";
            min_spawnpoints = MIN_ENEMIES;
            break;
        case ITEM_SPAWN:
            seq_name = "item_spawnpoints";
            min_spawnpoints = MIN_ITEMS;
            break;
        default:
            break;
    }

    out << YAML::Key << seq_name << YAML::Value << YAML::BeginSeq;

    // In case there are not enough spawnpoints, add some random ones
    if ((int)d_rects.size() <= min_spawnpoints) {

        for (int i = (int)d_rects.size(); i < min_spawnpoints; i++) {
            out << YAML::BeginMap;
            out << YAML::Key << "x" << YAML::Value
                << std::rand() % (resource_pool->get_config()->map_ed_max_width - TILE_SIZE) +
                            TILE_SIZE;
            out << YAML::Key << "y" << YAML::Value
                << std::rand() % (resource_pool->get_config()->map_ed_max_height / 2) + TILE_SIZE;
            out << YAML::EndMap;
        }
    }

    for (const auto& d_rect: d_rects) {
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << d_rect.x;
        out << YAML::Key << "y" << YAML::Value << d_rect.y - TILE_SIZE;
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
}

void SaveExitEditorButton::add_metadata(YAML::Emitter& out) {
    // Emit YAML for the map
    auto editor_yaml = *resource_pool->get_yaml(EDITOR_FILE);
    auto background_yaml = editor_yaml["background"];
    SDL_Rect back_s_rect = {background_yaml["x"].as<int>(), background_yaml["y"].as<int>(),
                            background_yaml["w"].as<int>(), background_yaml["h"].as<int>()};
    SDL_Rect back_d_rect = {0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT};

    out << YAML::Key << "map_width" << YAML::Value << resource_pool->get_config()->map_ed_max_width;
    out << YAML::Key << "map_height" << YAML::Value
        << resource_pool->get_config()->map_ed_max_height;
    out << YAML::Key << "background";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "s_rect";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << back_s_rect.x;
    out << YAML::Key << "y" << YAML::Value << back_s_rect.y;
    out << YAML::Key << "w" << YAML::Value << back_s_rect.w;
    out << YAML::Key << "h" << YAML::Value << back_s_rect.h;
    out << YAML::EndMap;  // End s_rect map
    out << YAML::Key << "d_rect";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << back_d_rect.x;
    out << YAML::Key << "y" << YAML::Value << back_d_rect.y;
    out << YAML::Key << "w" << YAML::Value << back_d_rect.w;
    out << YAML::Key << "h" << YAML::Value << back_d_rect.h;
    out << YAML::EndMap;  // End d_rect map
    out << YAML::EndMap;  // End background map
}

SaveExitEditorButton::~SaveExitEditorButton() = default;
