#include "map.h"

Map::Map(const map_list_t& map_enum, std::shared_ptr<engine::ResourcePool> resource_pool):
        background(nullptr), resource_pool(resource_pool), area({0, 0, 0, 0}) {
    std::string map_name = map_list_to_string.at(map_enum);
    load_map(map_name);
}

void Map::draw(SDL_Renderer* renderer, int it) {
    for (auto& sprite: sprites) {
        sprite.draw(renderer, it);
    }
}

void Map::draw_in_camera(SDL_Renderer* renderer, SDL_Rect& camera, int it) {
    background->draw(renderer, it);
    for (auto& sprite: sprites) {
        if (sprite.is_intersecting(camera)) {
            SDL_Rect& body = sprite.get_body();

            // calculate the sprite's position on the screen
            int x = body.x - camera.x;
            int y = body.y - camera.y;

            // draw the sprite
            sprite.set_position(x, y);
            sprite.draw(renderer, it);
        }
    }
}

void Map::load_map(const std::string& map_name) {
    auto texture = resource_pool->get_texture(map_name);
    auto yaml = *resource_pool->get_yaml(map_name);

    area.w = yaml["map_width"].as<int>();
    area.h = yaml["map_height"].as<int>();

    auto background_yaml = yaml["background"];
    SDL_Rect back_s_rect = {
            background_yaml["s_rect"]["x"].as<int>(), background_yaml["s_rect"]["y"].as<int>(),
            background_yaml["s_rect"]["w"].as<int>(), background_yaml["s_rect"]["h"].as<int>()};
    SDL_Rect back_d_rect = {
            background_yaml["d_rect"]["x"].as<int>(), background_yaml["d_rect"]["y"].as<int>(),
            background_yaml["d_rect"]["w"].as<int>(), background_yaml["d_rect"]["h"].as<int>()};
    background = std::make_unique<engine::Sprite>(texture, back_s_rect, back_d_rect);

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

SDL_Rect& Map::get_body() { return area; }

bool Map::is_intersecting(SDL_Rect& other) const { return SDL_HasIntersection(&area, &other); }

Map::~Map() = default;
