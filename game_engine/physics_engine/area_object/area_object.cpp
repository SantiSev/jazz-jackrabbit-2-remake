//
// Created by santi on 25/05/24.
//

#include "area_object.h"

AreaObject::AreaObject(int width, int height): ColisionObject(width, height) {}

void AreaObject::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        // TODO: aca debería haber un signal o algo indicando que el objecto recibio colision
        // Hay que indicar que fue 'colectado o tocado'
    }
}
