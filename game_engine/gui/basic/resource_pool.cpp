#include "resource_pool.h"

using engine::Font;
using engine::Music;
using engine::ResourcePool;
using engine::Sound;
using engine::SoundEffect;
using engine::Texture;

ResourcePool::ResourcePool(): renderer(nullptr), config(std::make_shared<Configuration>()) {}

ResourcePool::ResourcePool(SDL_Renderer* renderer):
        renderer(renderer), config(std::make_shared<Configuration>()) {}

void ResourcePool::load_texture(const std::string& name) {
    if (renderer == nullptr) {
        throw BadParams("Object was not initialized with a renderer");
    }
    std::string file = name + PNG_EXTENSION;
    if (textures.find(name) == textures.end()) {
        auto texture = std::make_shared<Texture>(asset_manager.get_full_path(file), renderer);
        textures.insert({name, texture});
    }
}

void ResourcePool::load_font(const std::string& name, int size) {
    if (renderer == nullptr) {
        throw BadParams("Object was not initialized with a renderer");
    }
    std::string file = name + TTF_EXTENSION;
    if (fonts.find(name) == fonts.end()) {
        auto font = std::make_shared<Font>(asset_manager.get_full_path(file), size);
        fonts.insert({name, font});
    }
}

void ResourcePool::load_yaml(const std::string& name) {
    std::string file = name + YAML_EXTENSION;
    if (yamls.find(name) == yamls.end()) {
        auto yaml = std::make_shared<YAML::Node>(YAML::LoadFile(asset_manager.get_full_path(file)));
        yamls.insert({name, yaml});
    }
}

void ResourcePool::load_sound_effect(const std::string& name) {
    std::string file = name + WAV_EXTENSION;
    if (sounds.find(name) == sounds.end()) {
        auto sound = std::make_shared<SoundEffect>(asset_manager.get_full_path(file));
        sounds.insert({name, sound});
    }
}

void ResourcePool::load_music(const std::string& name) {
    std::string file = name + MP3_EXTENSION;
    if (sounds.find(name) == sounds.end()) {
        auto sound = std::make_shared<Music>(asset_manager.get_full_path(file));
        sounds.insert({name, sound});
    }
}

void engine::ResourcePool::load_config(const std::string& name) {
    config->load_yaml_info(get_yaml(name));
    //        config->load_yaml_info(YAML::LoadFile(asset_manager.get_full_path(file)));
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
const std::shared_ptr<Sound>& ResourcePool::get_sound(const std::string& name) const {
    return sounds.at(name);
}
const std::shared_ptr<Configuration>& engine::ResourcePool::get_config() const { return config; }

ResourcePool::~ResourcePool() = default;
