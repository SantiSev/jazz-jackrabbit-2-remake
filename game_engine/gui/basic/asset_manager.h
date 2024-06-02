#ifndef TP_FINAL_ASSET_MANAGER_H
#define TP_FINAL_ASSET_MANAGER_H

#include <string>

#include <SDL2/SDL.h>

#include "../../errors.h"

class AssetManager {
private:
    char* base_path;

public:
    AssetManager();

    std::string get_full_path(const std::string& file) const;

    ~AssetManager();
};

#endif  // TP_FINAL_ASSET_MANAGER_H
