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

    out << YAML::Key << "objects" << YAML::Value << YAML::BeginMap;

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
                break;
            case ENEMY_SPAWN:
                enemy_spawnpoints.push_back(d_rect);
                break;
            case ITEM_SPAWN:
                item_spawnpoints.push_back(d_rect);
                break;
            case NULL_TILE:
                continue;
            default:
                break;
        }

        // Emit YAML for the current tile
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
    }

    // End objects map
    out << YAML::EndMap;

    add_spawns(out, PLAYER_SPAWN, player_spawnpoints);
    add_spawns(out, ENEMY_SPAWN, enemy_spawnpoints);
    add_spawns(out, ITEM_SPAWN, item_spawnpoints);

    // End main map
    out << YAML::EndMap;

    // Write YAML to file
    std::ofstream fout("tiles.yaml");
    fout << out.c_str();
    fout.close();

    std::cout << "Data saved to tiles.yaml successfully." << std::endl;
}

void SaveExitEditorButton::add_spawns(YAML::Emitter& out, TileType type,
                                      std::list<SDL_Rect> d_rects) {
    std::string seq_name;
    switch (type) {
        case PLAYER_SPAWN:
            seq_name = "player_spawnpoints";
            break;
        case ENEMY_SPAWN:
            seq_name = "enemy_spawnpoints";
            break;
        case ITEM_SPAWN:
            seq_name = "item_spawnpoints";
            break;
        default:
            break;
    }

    out << YAML::Key << seq_name << YAML::Value << YAML::BeginSeq;
    if (d_rects.empty()) {
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << std::rand() % (1280 - 32);
        out << YAML::Key << "y" << YAML::Value << std::rand() % (640 / 2);
        out << YAML::EndMap;
    }
    for (const auto& d_rect: d_rects) {
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << d_rect.x;
        out << YAML::Key << "y" << YAML::Value << d_rect.y;
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
}

void SaveExitEditorButton::add_metadata(YAML::Emitter& out) {
    // Emit YAML for the map
    SDL_Rect s_rect = {0, 1154, 255, 255};
    SDL_Rect d_rect = {0, 0, 800, 600};

    out << YAML::Key << "map_width" << YAML::Value << 1280;
    out << YAML::Key << "map_height" << YAML::Value << 640;
    out << YAML::Key << "background";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "s_rect";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << s_rect.x;
    out << YAML::Key << "y" << YAML::Value << s_rect.y;
    out << YAML::Key << "w" << YAML::Value << s_rect.w;
    out << YAML::Key << "h" << YAML::Value << s_rect.h;
    out << YAML::EndMap;  // End s_rect map
    out << YAML::Key << "d_rect";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << d_rect.x;
    out << YAML::Key << "y" << YAML::Value << d_rect.y;
    out << YAML::Key << "w" << YAML::Value << d_rect.w;
    out << YAML::Key << "h" << YAML::Value << d_rect.h;
    out << YAML::EndMap;  // End d_rect map
    out << YAML::EndMap;  // End background map
}

SaveExitEditorButton::~SaveExitEditorButton() = default;
