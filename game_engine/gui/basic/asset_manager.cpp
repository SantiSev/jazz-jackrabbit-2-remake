#include "asset_manager.h"

AssetManager::AssetManager() {
    base_path = SDL_GetBasePath();
    if (base_path == nullptr) {
        throw SDLError("Error getting base path: " + std::string(SDL_GetError()));
    }
}

std::string AssetManager::get_full_path(const std::string& file) const {
    return std::string(base_path) + file;
}

AssetManager::~AssetManager() { SDL_free(base_path); }
