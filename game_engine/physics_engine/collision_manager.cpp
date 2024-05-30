//
// Created by santi on 28/05/24.
//

#include "collision_manager.h"

CollisionManager::CollisionManager(int levelWidth, int levelHeight):
        gridWidth(levelWidth), gridHeight(levelHeight) {}


ColisionObject* CollisionManager::getColisionObjectAt(int x, int y) const {
    if (isValidCell(x, y)) {
        return grid[x][y];
    }
    return nullptr;
}

void CollisionManager::addObject(ColisionObject* obj) {

    Vector2D position = obj->get_position();

    int x = position.get_x();
    int y = position.get_y();

    if (isValidCell(x, y)) {
        grid[x][y] = obj;
    }
}

void CollisionManager::removeObject(ColisionObject* obj) {
    Vector2D position = obj->get_position();

    int x = position.get_x();
    int y = position.get_y();

    if (isValidCell(x, y) && grid[x][y] == obj) {
        grid[x][y] = nullptr;
    }
}

void CollisionManager::updateObject(ColisionObject* obj) {
    removeObject(obj);
    addObject(obj);
}
