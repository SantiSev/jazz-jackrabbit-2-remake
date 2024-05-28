//
// Created by santi on 28/05/24.
//

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>

#include "../math/vector2D.h"

#include "colision_object.h"


class CollisionManager {
private:
    int gridWidth;
    int gridHeight;
    std::vector<std::vector<ColisionObject*>> grid;  // grid: [x][y] stores a collisionObject

    Vector2D getCellCoords(int x, int y) const { return Vector2D(x, y); }

    bool isValidCell(int x, int y) const {
        return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
    }

public:
    CollisionManager(int levelWidth, int levelHeight);

    void addObject(ColisionObject* obj);
    void removeObject(ColisionObject* obj);
    void updateObject(ColisionObject* obj, const Vector2D& oldPosition);
    void clear();
};


#endif  // COLLISION_MANAGER_H
