#include "map.h"

Map::Map(const std::string& tileset_name, const std::string& yaml_name,
         std::shared_ptr<engine::ResourcePool> resource_pool):
        resource_pool(resource_pool) {
    load_map(tileset_name, yaml_name);
}

void Map::draw(SDL_Renderer* renderer) {
    for (auto& sprite: sprites) {
        sprite.draw(renderer);
    }
}

void Map::load_map(const std::string& tileset_name, const std::string& yaml_name) {
    auto texture = resource_pool->get_texture(tileset_name);
    YAML::Node yaml = YAML::LoadFile(asset_manager.get_full_path(yaml_name));

    for (auto obj: yaml["objects"]) {
        auto s_rect_yaml = obj["s_rect"];
        SDL_Rect s_rect = {s_rect_yaml["x"].as<int>(), s_rect_yaml["y"].as<int>(),
                           s_rect_yaml["w"].as<int>(), s_rect_yaml["h"].as<int>()};

        auto d_rect_list_yaml = obj["d_rect_list"];
        for (auto d_rect_obj: d_rect_list_yaml) {
            auto d_rect_yaml = d_rect_obj["d_rect"];

            auto repeat_h = d_rect_yaml["repeat_h"].as<int>();
            auto repeat_v = d_rect_yaml["repeat_v"].as<int>();

            auto x = d_rect_yaml["x"].as<int>();
            auto y = d_rect_yaml["y"].as<int>();
            auto w = d_rect_yaml["w"].as<int>();
            auto h = d_rect_yaml["h"].as<int>();

            // Repeat horizontally
            for (int i = 0; i < repeat_h; i++) {
                SDL_Rect d_rect = {x + i * w, y, w, h};
                sprites.emplace_back(texture, s_rect, d_rect);
            }

            // Repeat vertically starting from the second tile (to avoid repeating the first tile)
            for (int i = 1; i < repeat_v; i++) {
                SDL_Rect d_rect = {x, y - i * h, w, h};
                sprites.emplace_back(texture, s_rect, d_rect);
            }
        }
    }
}

Map::~Map() = default;