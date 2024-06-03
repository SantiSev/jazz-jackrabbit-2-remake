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

std::shared_ptr<Texture>& ResourcePool::get_texture(const std::string& name) {
    return textures[name];
}

std::shared_ptr<Font>& ResourcePool::get_font(const std::string& name) { return fonts[name]; }

ResourcePool::~ResourcePool() = default;
