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
#include "texture.h"

#define PNG_EXTENSION ".png"
#define YAML_EXTENSION ".yaml"
#define TTF_EXTENSION ".ttf"

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

public:
    // Load files that don't depend on the renderer only
    ResourcePool();

    // Load files that depend on the renderer or not
    explicit ResourcePool(SDL_Renderer* renderer);

    // cant copy
    ResourcePool(const ResourcePool&) = delete;
    ResourcePool& operator=(const ResourcePool&) = delete;

    const std::shared_ptr<Texture>& load_texture(const std::string& name);
    const std::shared_ptr<Font>& load_font(const std::string& name, int size);
    const std::shared_ptr<YAML::Node>& load_yaml(const std::string& name);

    // Thread-safe, read only getters
    const std::shared_ptr<Texture>& get_texture(const std::string& name) const;
    const std::shared_ptr<Font>& get_font(const std::string& name) const;
    const std::shared_ptr<YAML::Node>& get_yaml(const std::string& name) const;

    ~ResourcePool();
};
}  // namespace engine

#endif  // TP_FINAL_RESOURCE_POOL_H
