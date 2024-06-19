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

    // Create YAML emitter
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "objects" << YAML::Value << YAML::BeginSeq;

    // Iterate through tiles and export each EditorTile
    for (const auto& pair: map) {
        const auto& tile = pair.second;

        // Get s_rect data
        auto& s_rect = tile->get_s_rect();

        if (s_rect.x == 0 && s_rect.y == 0) {
            continue;
        }

        // Get d_rect data
        auto d_rect = tile->get_d_rect();

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

    out << YAML::EndSeq;
    out << YAML::EndMap;

    // Write YAML to file
    std::ofstream fout("tiles.yaml");
    fout << out.c_str();
    fout.close();

    std::cout << "Data saved to tiles.yaml successfully." << std::endl;
}

SaveExitEditorButton::~SaveExitEditorButton() = default;
