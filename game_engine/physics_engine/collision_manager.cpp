#include "collision_manager.h"

#include <algorithm>

#include "physics_object/dynamic_body.h"

CollisionManager::CollisionManager(int level_width, int level_height):
        grid_width(level_width),
        grid_height(level_height),
        grid(level_width, std::vector<std::shared_ptr<CollisionObject>>(level_height, nullptr)) {}

std::shared_ptr<CollisionObject> CollisionManager::get_collision_object_at(int x, int y) const {
    return grid[x][y];
}

void CollisionManager::place_object_in_grid(std::shared_ptr<CollisionObject> obj) {

    for (int i = obj->position.x; i < obj->position.x + obj->get_hitbox_width(); ++i) {
        for (int j = obj->position.y; j < obj->position.y + obj->get_hitbox_height(); ++j) {
            if (is_valid_cell(i, j) && grid[i][j] == nullptr) {
                grid[i][j] = obj;
            }
        }
    }
}

bool CollisionManager::is_valid_cell(int x, int y) const {
    return x >= 0 && x < grid_width && y >= 0 && y < grid_height;
}

void CollisionManager::remove_object_from_grid(std::shared_ptr<CollisionObject> obj,
                                               Vector2D position) {

    for (int i = position.x; i < position.x + obj->get_hitbox_width(); ++i) {
        for (int j = position.y; j < position.y + obj->get_hitbox_height(); ++j) {
            if (is_valid_cell(i, j) && grid[i][j] == obj) {
                grid[i][j] = nullptr;
            }
        }
    }
}


// ----------------- public methods ---------------------


bool CollisionManager::can_be_placed(std::shared_ptr<CollisionObject> obj) const {
    for (int i = obj->position.x; i < obj->position.x + obj->get_hitbox_width(); ++i) {
        for (int j = obj->position.y; j < obj->position.y + obj->get_hitbox_height(); ++j) {
            if (grid[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

void CollisionManager::add_object(std::shared_ptr<StaticBody> obj) { place_object_in_grid(obj); }

void CollisionManager::track_dynamic_body(std::shared_ptr<DynamicBody> obj) {
    dynamic_bodies.emplace_back(obj, obj->position);
    place_object_in_grid(obj);
}

void CollisionManager::remove_object(std::shared_ptr<CollisionObject> obj) {
    remove_object_from_grid(obj, obj->position);
}

void CollisionManager::update_object(std::shared_ptr<CollisionObject> obj) {
    remove_object_from_grid(obj, obj->position);
    place_object_in_grid(obj);
}

void CollisionManager::detect_colisions(std::shared_ptr<DynamicBody> obj) {
    // Get the position and hitbox dimensions of the obj
    int obj_x = obj->position.x;
    int obj_y = obj->position.y;
    int obj_width = obj->get_hitbox_width();
    int obj_height = obj->get_hitbox_height();

    if (obj_x < 0 || obj_y < 0 || obj_x + obj_width > grid_width ||
        obj_y + obj_height > grid_height) {
        return;
    }

    for (int i = obj_x; i < obj_x + obj_width; ++i) {
        for (int j = obj_y; j < obj_y + obj_height; ++j) {
            std::shared_ptr<CollisionObject> other = get_collision_object_at(i, j);
            if (other != nullptr && other.get() != obj.get()) {
                // double dispatch to handle collision
                obj->handle_colision(other.get());  // Handle collision with other object
                other->handle_colision(obj.get());  // Handle collision with obj
            }
        }
    }
}

void CollisionManager::handle_out_of_bounds(std::shared_ptr<DynamicBody> obj) {
    if (obj->position.x < 0) {
        obj->position.x = 32;
        obj->velocity.x = 0;
    } else if (obj->position.x + obj->get_hitbox_width() > grid_width) {
        obj->position.x = (grid_width - obj->get_hitbox_width() - 32);
        obj->velocity.x = 0;
    }

    if (obj->position.y < 0) {
        obj->position.y = 32;

    } else if (obj->position.y + obj->get_hitbox_height() > grid_height) {
        // set the position to the middle of the map
        obj->position.y = (grid_height - obj->get_hitbox_height() - 32);
    }
}

void CollisionManager::update() {  // create to update specific object
    // Use an iterator to iterate over the dynamic_bodies tuple

    if (dynamic_bodies.empty()) {
        return;
    }

    for (auto it = dynamic_bodies.begin(); it != dynamic_bodies.end();) {

        auto& obj = std::get<0>(*it);

        if (obj != nullptr || !obj->is_active_object()) {
            auto& old_position_ref = std::get<1>(*it);

            obj->update_body();

            detect_colisions(obj);  // Detect collisions with other objects

            handle_out_of_bounds(obj);  // Handle out of bounds

            if (obj->position != old_position_ref) {  // If the object has moved, update the grid
                remove_object_from_grid(obj, old_position_ref);
                place_object_in_grid(obj);
                old_position_ref = obj->position;  // Update the old position
            }

            ++it;  // Move to the next element
        }
    }
}

// create a method that removes all inactive objects from the grid
// and from the dynamic_bodies vector
// and then call this method from the update method

void CollisionManager::remove_inactive_bodies() {

    if (dynamic_bodies.empty()) {
        return;
    }

    for (auto it = dynamic_bodies.begin(); it != dynamic_bodies.end();) {
        auto& obj = std::get<0>(*it);

        if (!obj->is_active_object()) {
            remove_object_from_grid(obj, obj->position);
            it = dynamic_bodies.erase(it);
        } else {
            ++it;  // Move to the next element only if it wasn't erased
        }
    }
}

void CollisionManager::iterateDynamicBodies(
        std::function<void(std::shared_ptr<DynamicBody>&)> func) {
    for (auto& bodyTuple: dynamic_bodies) {
        auto& body = std::get<0>(bodyTuple);
        func(body);
    }
}


int CollisionManager::get_grid_width() const { return grid_width; }

int CollisionManager::get_grid_height() const { return grid_height; }

void CollisionManager::clear() {
    for (auto& column: grid) {
        std::fill(column.begin(), column.end(), nullptr);
    }
    dynamic_bodies.clear();
}


CollisionManager::~CollisionManager() {
    for (auto& column: grid) {
        column.clear();
        column.shrink_to_fit();
    }
    grid.clear();
    grid.shrink_to_fit();

    dynamic_bodies.clear();
    dynamic_bodies.shrink_to_fit();
}
