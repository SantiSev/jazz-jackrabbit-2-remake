//
// Created by santi on 28/05/24->
//

#include "collision_manager.h"

#include "physics_object/dynamic_body.h"

CollisionManager::CollisionManager(int level_width, int level_height):
        grid_width(level_width),
        grid_height(level_height),
        grid(level_width, std::vector<std::shared_ptr<CollisionObject>>(level_height, nullptr)) {}

std::shared_ptr<CollisionObject> CollisionManager::get_collision_object_at(int x, int y) const {
    return grid[x][y];
}

void CollisionManager::place_object_in_grid(std::shared_ptr<CollisionObject> obj) {

    for (int i = obj->get_position().get_x();
         i < obj->get_position().get_x() + obj->get_hitbox_width(); ++i) {
        for (int j = obj->get_position().get_y();
             j < obj->get_position().get_y() + obj->get_hitbox_height(); ++j) {
            if (is_valid_cell(i, j) && grid[i][j] == nullptr) {
                grid[i][j] = obj;
            }
        }
    }
}


void CollisionManager::remove_object_from_grid(std::shared_ptr<CollisionObject> obj,
                                               Vector2D position) {

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

void CollisionManager::detect_colisions(std::shared_ptr<DynamicBody> obj) {
    // Get the position and hitbox dimensions of the obj
    int obj_x = obj->get_position().get_x();
    int obj_y = obj->get_position().get_y();
    int obj_width = obj->get_hitbox_width();
    int obj_height = obj->get_hitbox_height();

    if (obj_x < 0 || obj_y < 0 || obj_x + obj_width > grid_width ||
        obj_y + obj_height > grid_height) {
        obj->revert_position();
        return;
    }

    for (int i = obj_x; i < obj_x + obj_width; ++i) {
        for (int j = obj_y; j < obj_y + obj_height; ++j) {
            std::shared_ptr<CollisionObject> other = get_collision_object_at(i, j);
            if (other != nullptr && other.get() != obj.get()) {
                other->handle_colision(*obj);
            }
        }
    }
}


void CollisionManager::update_dynamic_object(std::shared_ptr<DynamicBody> obj) {

    if (obj != nullptr) {
        detect_colisions(obj);
        if (obj->get_position() !=
            obj->get_update_position_reference()) {  // if the position wasn't changed during the
                                                     // colision detection process then don't update
                                                     // the object position in the grid!
            remove_object_from_grid(obj, obj->get_update_position_reference());
            place_object_in_grid(obj);
        }
    }
}

int CollisionManager::get_grid_width() const { return grid_width; }

int CollisionManager::get_grid_height() const { return grid_height; }

void CollisionManager::clear() {
    for (auto& column: grid) {
        std::fill(column.begin(), column.end(), nullptr);
    }
}
