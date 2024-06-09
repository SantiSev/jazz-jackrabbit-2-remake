#include "resource_pool.h"

using engine::Font;
using engine::ResourcePool;
using engine::Texture;

ResourcePool::ResourcePool(SDL_Renderer* renderer): renderer(renderer) {}

void ResourcePool::load_texture(const std::string& name) {
    if (textures.find(name) == textures.end()) {
        auto texture = std::make_shared<Texture>(asset_manager.get_full_path(name), renderer);
        textures[name] = texture;
    }
}

void ResourcePool::load_font(const std::string& name, int size) {
    if (fonts.find(name) == fonts.end()) {
        auto font = std::make_shared<Font>(asset_manager.get_full_path(name), size);
        fonts[name] = font;
    }
}

void ResourcePool::load_yaml(const std::string& name) {
    if (yamls.find(name) == yamls.end()) {
        auto yaml = std::make_shared<YAML::Node>(YAML::LoadFile(asset_manager.get_full_path(name)));
        yamls[name] = yaml;
    }
}

std::shared_ptr<Texture>& ResourcePool::get_texture(const std::string& name) {
    return textures.at(name);
}

std::shared_ptr<Font>& ResourcePool::get_font(const std::string& name) { return fonts.at(name); }

std::shared_ptr<YAML::Node>& ResourcePool::get_yaml(const std::string& name) {
    return yamls.at(name);
}

ResourcePool::~ResourcePool() = default;
