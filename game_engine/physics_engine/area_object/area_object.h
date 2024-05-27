//
// Created by santi on 25/05/24.
//

#ifndef AREA_OBJECT_H
#define AREA_OBJECT_H
#include "../colision_object.h"


class AreaObject: ColisionObject {
public:
    AreaObject(int width, int height);
    void handle_colision(ColisionObject& other) override;
};


#endif  // AREA_OBJECT_H
