#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <list>
#include <memory>
#include <string>

#include <yaml-cpp/yaml.h>

#include "../../common/assets.h"
#include "../../common/map_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/camera.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/sprite.h"

class Map: public engine::CanvasObject {
private:
    std::unique_ptr<engine::Sprite> background;
    std::list<engine::Sprite> sprites;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    SDL_Rect area;

    void load_map(const uint16_t& map_id);

public:
    Map(const uint16_t& map_id, std::shared_ptr<engine::ResourcePool> resource_pool);

    void draw(SDL_Renderer* renderer, int it) override;
    void draw_in_camera(SDL_Renderer* renderer, engine::Camera& camera, int it);

    SDL_Rect& get_body() override;

    bool is_intersecting(SDL_Rect& other) const override;

    ~Map() override;
};

#endif  // TP_FINAL_MAP_H
