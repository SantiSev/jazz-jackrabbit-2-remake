//
// Created by santi on 24/05/24.
//

#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../colision_object.h"

class DynamicBody: public CollisionObject {
public:
    Vector2D velocity = Vector2D(0, 0);

    DynamicBody(int width, int height);
    DynamicBody(int x, int y, int width, int height);
    DynamicBody(int x, int y, int width, int height, Vector2D base_speed);


    virtual void update_db();

    void handle_colision(CollisionObject& other) override;

    virtual void print_info();
};


#endif  // CHARACTER_BODY_H
