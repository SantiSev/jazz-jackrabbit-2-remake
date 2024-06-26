
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <functional>
#include <memory>
#include <tuple>
#include <vector>

#include "../math/vector2D.h"
#include "physics_object/dynamic_body.h"
#include "physics_object/static_body.h"

#include "collision_object.h"
namespace engine {
class CollisionManager {
private:
    int grid_width;
    int grid_height;
    std::vector<std::vector<std::shared_ptr<engine::CollisionObject>>>
            grid;  // grid: [x][y] stores a vector of shared pointers to engine::CollisionObjects

    std::vector<std::tuple<std::shared_ptr<engine::DynamicBody>, engine::Vector2D>> dynamic_bodies;
    std::vector<std::shared_ptr<engine::StaticBody>> static_bodies;

    void handle_out_of_bounds(std::shared_ptr<engine::DynamicBody> obj);
    void place_object_in_grid(std::shared_ptr<engine::CollisionObject> obj);
    void remove_object_from_grid(std::shared_ptr<engine::CollisionObject> obj,
                                 engine::Vector2D position);

    bool is_valid_cell(int x, int y) const;
    void detect_colisions(std::shared_ptr<engine::DynamicBody> obj);
    void clear();

public:
    CollisionManager(int levelWidth, int levelHeight);
    void iterateDynamicBodies(std::function<void(std::shared_ptr<engine::DynamicBody>&)> func);
    std::shared_ptr<engine::CollisionObject> get_collision_object_at(int x, int y) const;
    void add_object(std::shared_ptr<engine::StaticBody> obj);
    void track_dynamic_body(std::shared_ptr<engine::DynamicBody> obj);
    bool can_be_placed(std::shared_ptr<engine::CollisionObject> obj,
                       engine::Vector2D new_position) const;
    void remove_object(std::shared_ptr<engine::CollisionObject> obj);
    void update_object(std::shared_ptr<engine::CollisionObject> obj);
    void update();
    void remove_inactive_bodies();
    int get_grid_width() const;
    int get_grid_height() const;
    void prepare_map();


    ~CollisionManager();
};
}  // namespace engine


#endif  // COLLISION_MANAGER_H
