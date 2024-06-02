//
// Created by santi on 28/05/24.
//

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H


#include <memory>
#include <vector>

#include "../math/vector2D.h"
#include "physics_object/dynamic_body.h"

#include "colision_object.h"


class CollisionManager {
private:
    int grid_width;
    int grid_height;
    std::vector<std::vector<std::shared_ptr<CollisionObject>>>
            grid;  // grid: [x][y] stores a vector of shared pointers to CollisionObjects

    void place_object_in_grid(std::shared_ptr<CollisionObject> obj);
    void remove_object_from_grid(std::shared_ptr<CollisionObject> obj, Vector2D position);

    bool is_valid_cell(int x, int y) const {
        return x >= 0 && x < grid_width && y >= 0 && y < grid_height;
    }

    void detect_colisions(std::shared_ptr<DynamicBody> obj);

public:
    CollisionManager(int levelWidth, int levelHeight);

    std::shared_ptr<CollisionObject> get_collision_object_at(int x, int y) const;
    void add_object(std::shared_ptr<CollisionObject> obj);
    void remove_object(std::shared_ptr<CollisionObject> obj);
    void update_object(std::shared_ptr<CollisionObject> obj);
    void update_dynamic_object(std::shared_ptr<DynamicBody> obj);


    void clear();
};


#endif  // COLLISION_MANAGER_H
