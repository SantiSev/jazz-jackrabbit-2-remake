//
// Created by santi on 24/05/24.
//

#ifndef STATIC_BODY_H
#define STATIC_BODY_H
#include "../colision_object/colision_object.h"


class StaticBody: public ColisionObject {

public:
    StaticBody(float width, float height);
};


#endif  // STATIC_BODY_H
