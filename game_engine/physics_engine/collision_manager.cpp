//
// Created by santi on 28/05/24->
//

#include "collision_manager.h"

CollisionManager::CollisionManager(int level_width, int level_height)
    : grid_width(level_width), grid_height(level_height), grid(level_width, std::vector<std::shared_ptr<CollisionObject>>(level_height, nullptr)) {}

std::shared_ptr<CollisionObject> CollisionManager::get_collision_object_at(int x, int y) const {
    return grid[x][y];
}

void CollisionManager::place_object_in_grid(std::shared_ptr<CollisionObject> obj) {

    for (int i = obj->get_position().get_x(); i < obj->get_position().get_x() + obj->get_hitbox_width(); ++i) {
        for (int j = obj->get_position().get_y(); j < obj->get_position().get_y() + obj->get_hitbox_height(); ++j) {
            if (is_valid_cell(i, j)) {
                grid[i][j] = obj;
            }
        }
    }
}


void CollisionManager::remove_object_from_grid(std::shared_ptr<CollisionObject> obj, Vector2D position) {

    for (int i = position.get_x(); i < position.get_x() + obj->get_hitbox_width(); ++i) {
        for (int j = position.get_y(); j < position.get_y() + obj->get_hitbox_height(); ++j) {
            if (is_valid_cell(i, j) && grid[i][j] == obj) {
                grid[i][j] = nullptr;
            }
        }
    }

}

void CollisionManager::add_object(std::shared_ptr<CollisionObject> obj) {
    place_object_in_grid(obj);
}

void CollisionManager::remove_object(std::shared_ptr<CollisionObject> obj) {
    remove_object_from_grid(obj, obj->get_position());
}

void CollisionManager::update_object(std::shared_ptr<CollisionObject> obj) {
    remove_object_from_grid(obj, obj->get_position());
    place_object_in_grid(obj);
}

void CollisionManager::update__dynamic_object(std::shared_ptr<DynamicBody> obj, Vector2D old_position) {
    remove_object_from_grid(obj, old_position);
    place_object_in_grid(obj);
}

void CollisionManager::clear() {
    for (auto& column : grid) {
        std::fill(column.begin(), column.end(), nullptr);
    }
}



