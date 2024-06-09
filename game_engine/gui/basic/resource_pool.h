#ifndef TP_FINAL_RESOURCE_POOL_H
#define TP_FINAL_RESOURCE_POOL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>

#include "asset_manager.h"
#include "font.h"
#include "texture.h"

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
    explicit ResourcePool(SDL_Renderer* renderer);

    // cant copy
    ResourcePool(const ResourcePool&) = delete;
    ResourcePool& operator=(const ResourcePool&) = delete;

    void load_texture(const std::string& name);
    void load_font(const std::string& name, int size);
    void load_yaml(const std::string& name);

    std::shared_ptr<Texture>& get_texture(const std::string& name);
    std::shared_ptr<Font>& get_font(const std::string& name);
    std::shared_ptr<YAML::Node>& get_yaml(const std::string& name);

    ~ResourcePool();
};
}  // namespace engine

#endif  // TP_FINAL_RESOURCE_POOL_H
