#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <list>
#include <memory>
#include <string>

#include <yaml-cpp/yaml.h>

#include "../../common/assets.h"
#include "../../common/map_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"

class Map: public engine::CanvasObject {
private:
    std::list<engine::Sprite> sprites;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    void load_map(const std::string& tileset_name, const std::string& yaml_name);

public:
    Map(const map_list_t& map_enum, std::shared_ptr<engine::ResourcePool> resource_pool);

    void draw(SDL_Renderer* renderer) override;

    ~Map() override;
};

#endif  // TP_FINAL_MAP_H
