//
// Created by santi on 25/05/24.
//

#ifndef AREA_OBJECT_H
#define AREA_OBJECT_H
#include "../colision_object.h"


class AreaObject: public ColisionObject {

protected:
    // TODO finish implementing this method
    virtual void handle_colision(ColisionObject& other);

public:
    AreaObject(int width, int height);
    void detect_colision(ColisionObject& other) override;
};


#endif  // AREA_OBJECT_H
