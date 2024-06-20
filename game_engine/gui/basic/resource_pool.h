#ifndef TP_FINAL_RESOURCE_POOL_H
#define TP_FINAL_RESOURCE_POOL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>

#include "../../errors.h"

#include "asset_manager.h"
#include "font.h"
#include "music.h"
#include "sound_effect.h"
#include "texture.h"

#define PNG_EXTENSION ".png"
#define YAML_EXTENSION ".yaml"
#define TTF_EXTENSION ".ttf"
#define WAV_EXTENSION ".wav"
#define MP3_EXTENSION ".mp3"

namespace engine {
// Uses a path pseudo-relative to the project root directory to load and retrieve resources
// Example: "assets/images/texture.png"
class ResourcePool {
private:
    SDL_Renderer* renderer;
    AssetManager asset_manager;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<Font>> fonts;
    std::unordered_map<std::string, std::shared_ptr<YAML::Node>> yamls;
    std::unordered_map<std::string, std::shared_ptr<Sound>> sounds;

public:
    // Load files that don't depend on the renderer only
    ResourcePool();

    // Load files that depend on the renderer or not
    explicit ResourcePool(SDL_Renderer* renderer);

    // cant copy
    ResourcePool(const ResourcePool&) = delete;
    ResourcePool& operator=(const ResourcePool&) = delete;

    void load_texture(const std::string& name);
    void load_font(const std::string& name, int size);
    void load_yaml(const std::string& name);
    void load_sound_effect(const std::string& name);
    void load_music(const std::string& name);

    // Thread-safe, read only getters
    const std::shared_ptr<Texture>& get_texture(const std::string& name) const;
    const std::shared_ptr<Font>& get_font(const std::string& name) const;
    const std::shared_ptr<YAML::Node>& get_yaml(const std::string& name) const;
    const std::shared_ptr<Sound>& get_sound(const std::string& name) const;

    ~ResourcePool();
};
}  // namespace engine

#endif  // TP_FINAL_RESOURCE_POOL_H
