//
// Created by santi on 24/05/24.
//

#ifndef STATIC_BODY_H
#define STATIC_BODY_H
#include "../colision_object.h"


class StaticBody: public ColisionObject {

protected:
    void handle_colision(CollisionFace face, ColisionObject& other) const;

public:
    void detect_colision(ColisionObject& other) override;
    StaticBody(int width, int height);
};


#endif  // STATIC_BODY_H
