#include "collision_manager.h"

#include <algorithm>

#include "physics_object/dynamic_body.h"

using engine::CollisionManager;

CollisionManager::CollisionManager(int level_width, int level_height):
        grid_width(level_width),
        grid_height(level_height),
        grid(level_width,
             std::vector<std::shared_ptr<engine::CollisionObject>>(level_height, nullptr)) {}

std::shared_ptr<engine::CollisionObject> CollisionManager::get_collision_object_at(int x,
                                                                                   int y) const {
    return grid[x][y];
}

void CollisionManager::place_object_in_grid(std::shared_ptr<engine::CollisionObject> obj) {

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

void CollisionManager::remove_object_from_grid(std::shared_ptr<engine::CollisionObject> obj,
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


bool CollisionManager::can_be_placed(std::shared_ptr<engine::CollisionObject> obj,
                                     Vector2D new_position) const {
    for (int i = new_position.x; i < new_position.x + obj->get_hitbox_width(); ++i) {
        for (int j = new_position.y; j < new_position.y + obj->get_hitbox_height(); ++j) {
            if (grid[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

void CollisionManager::add_object(std::shared_ptr<engine::StaticBody> obj) {

    static_bodies.emplace_back(obj);
    place_object_in_grid(obj);
}

void CollisionManager::track_dynamic_body(std::shared_ptr<engine::DynamicBody> obj) {

    dynamic_bodies.emplace_back(obj, obj->position);
    place_object_in_grid(obj);
}

void CollisionManager::remove_object(std::shared_ptr<engine::CollisionObject> obj) {
    remove_object_from_grid(obj, obj->position);
}

void CollisionManager::update_object(std::shared_ptr<engine::CollisionObject> obj) {
    remove_object_from_grid(obj, obj->position);
    place_object_in_grid(obj);
}

void CollisionManager::detect_colisions(std::shared_ptr<engine::DynamicBody> obj) {

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
            std::shared_ptr<engine::CollisionObject> other = get_collision_object_at(i, j);
            if (other != nullptr && other.get() != obj.get()) {
                // double dispatch to handle collision
                obj->handle_colision(other.get());  // Handle collision with other object
                other->handle_colision(obj.get());  // Handle collision with obj
            }
        }
    }
}

void CollisionManager::handle_out_of_bounds(
        std::shared_ptr<engine::DynamicBody> obj) {  // TODO refactor this :D
    if (obj->position.x < 0) {
        obj->position.x = 32;
        obj->velocity.x = 0;
        obj->handle_out_of_bounds();
    } else if (obj->position.x + obj->get_hitbox_width() > grid_width) {
        obj->position.x = (grid_width - obj->get_hitbox_width() - 32);
        obj->velocity.x = 0;
        obj->handle_out_of_bounds();
    }

    if (obj->position.y < 0) {
        obj->position.y = 32;
        obj->handle_out_of_bounds();

    } else if (obj->position.y + obj->get_hitbox_height() > grid_height) {
        // set the position to the middle of the map
        obj->position.y = (grid_height - obj->get_hitbox_height() - 32);
        obj->handle_out_of_bounds();
    }
}

void CollisionManager::update() {

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
            ++it;
        }
    }
}

void CollisionManager::iterateDynamicBodies(
        std::function<void(std::shared_ptr<engine::DynamicBody>&)> func) {
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

    static_bodies.clear();
    static_bodies.shrink_to_fit();
}

void CollisionManager::prepare_map() {
    for (auto& static_body: static_bodies) {
        int startX = static_body->position.x;
        int startY = static_body->position.y;
        int endX = startX + static_body->get_hitbox_width();
        int endY = startY + static_body->get_hitbox_height();

        // Check each side of the static body
        for (int i = startX; i < endX; ++i) {
            for (int j = startY; j < endY; ++j) {

                // Check left adjacent cell
                if (is_valid_cell(i - 1, j)) {
                    auto coll_obj = get_collision_object_at(i - 1, j);
                    engine::StaticBody* adj_obj = dynamic_cast<engine::StaticBody*>(
                            get_collision_object_at(i - 1, j).get());

                    if (adj_obj && adj_obj->position.x + adj_obj->get_hitbox_width() ==
                                           static_body->position.x) {
                        static_body->disable_collision(CollisionFace::LEFT);
                        adj_obj->disable_collision(CollisionFace::RIGHT);
                    }
                }

                // Check right adjacent cell
                if (is_valid_cell(i + 1, j)) {
                    auto coll_obj = get_collision_object_at(i + 1, j);
                    engine::StaticBody* adj_obj = dynamic_cast<engine::StaticBody*>(coll_obj.get());
                    if (adj_obj && adj_obj->position.x == static_body->position.x +
                                                                  static_body->get_hitbox_width()) {
                        static_body->disable_collision(CollisionFace::RIGHT);
                        adj_obj->disable_collision(CollisionFace::LEFT);
                    }
                }

                // Check top adjacent cell
                if (is_valid_cell(i, j - 1)) {
                    auto coll_obj = get_collision_object_at(i, j - 1);
                    engine::StaticBody* adj_obj = dynamic_cast<engine::StaticBody*>(coll_obj.get());
                    if (adj_obj && adj_obj->position.y + adj_obj->get_hitbox_height() ==
                                           static_body->position.y) {
                        static_body->disable_collision(CollisionFace::TOP);
                        adj_obj->disable_collision(CollisionFace::BOTTOM);
                    }
                }

                // Check bottom adjacent cell
                if (is_valid_cell(i, j + 1)) {
                    auto coll_obj = get_collision_object_at(i, j + 1);
                    engine::StaticBody* adj_obj = dynamic_cast<engine::StaticBody*>(coll_obj.get());
                    if (adj_obj &&
                        adj_obj->position.y ==
                                static_body->position.y + static_body->get_hitbox_height()) {
                        static_body->disable_collision(CollisionFace::BOTTOM);
                        adj_obj->disable_collision(CollisionFace::TOP);
                    }
                }
            }
        }
    }
}
