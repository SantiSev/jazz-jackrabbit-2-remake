#include "map.h"

Map::Map(const std::string& tileset_name, const std::string& yaml_name,
         std::shared_ptr<engine::ResourcePool> resource_pool):
        resource_pool(resource_pool) {
    YAML::Node map = YAML::LoadFile(asset_manager.get_full_path(yaml_name));
    auto texture = resource_pool->get_texture(tileset_name);
    for (auto obj: map["objects"]) {
        auto s_rect_yaml = obj["s_rect"];
        auto d_rect_yaml = obj["d_rect"];
        SDL_Rect s_rect = {s_rect_yaml["x"].as<int>(), s_rect_yaml["y"].as<int>(),
                           s_rect_yaml["w"].as<int>(), s_rect_yaml["h"].as<int>()};
        SDL_Rect d_rect = {d_rect_yaml["x"].as<int>(), d_rect_yaml["y"].as<int>(),
                           d_rect_yaml["w"].as<int>(), d_rect_yaml["h"].as<int>()};
        sprites.emplace_back(texture, s_rect, d_rect);
    }
}

void Map::draw(SDL_Renderer* renderer) {
    for (auto& sprite: sprites) {
        sprite.draw(renderer);
    }
}

Map::~Map() = default;
