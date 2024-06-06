#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <list>
#include <memory>
#include <string>

#include <yaml-cpp/yaml.h>

#include "../../game_engine/gui/basic/asset_manager.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../assets.h"

class Map: public engine::CanvasObject {
private:
    std::list<engine::Sprite> sprites;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    engine::AssetManager asset_manager;

    void load_map(const std::string& tileset_name, const std::string& yaml_name);

public:
    Map(const std::string& tileset_name, const std::string& yaml_name,
        std::shared_ptr<engine::ResourcePool> resource_pool);

    void draw(SDL_Renderer* renderer) override;

    ~Map() override;
};

#endif  // TP_FINAL_MAP_H
