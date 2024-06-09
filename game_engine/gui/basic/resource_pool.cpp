#include "resource_pool.h"

using engine::Font;
using engine::ResourcePool;
using engine::Texture;

ResourcePool::ResourcePool(): renderer(nullptr) {}

ResourcePool::ResourcePool(SDL_Renderer* renderer): renderer(renderer) {}

void ResourcePool::load_texture(const std::string& name) {
    if (renderer == nullptr) {
        throw BadParams("Object was not initialized with a renderer");
    }
    std::string file = name + PNG_EXTENSION;
    if (textures.find(name) == textures.end()) {
        auto texture = std::make_shared<Texture>(asset_manager.get_full_path(file), renderer);
        textures[name] = texture;
    }
}

void ResourcePool::load_font(const std::string& name, int size) {
    if (renderer == nullptr) {
        throw BadParams("Object was not initialized with a renderer");
    }
    std::string file = name + TTF_EXTENSION;
    if (fonts.find(name) == fonts.end()) {
        auto font = std::make_shared<Font>(asset_manager.get_full_path(file), size);
        fonts[name] = font;
    }
}

void ResourcePool::load_yaml(const std::string& name) {
    std::string file = name + YAML_EXTENSION;
    if (yamls.find(name) == yamls.end()) {
        auto yaml = std::make_shared<YAML::Node>(YAML::LoadFile(asset_manager.get_full_path(file)));
        yamls[name] = yaml;
    }
}

const std::shared_ptr<Texture>& ResourcePool::get_texture(const std::string& name) const {
    return textures.at(name);
}

const std::shared_ptr<Font>& ResourcePool::get_font(const std::string& name) const {
    return fonts.at(name);
}

const std::shared_ptr<YAML::Node>& ResourcePool::get_yaml(const std::string& name) const {
    return yamls.at(name);
}

ResourcePool::~ResourcePool() = default;
