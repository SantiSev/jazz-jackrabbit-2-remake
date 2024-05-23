//
// Created by santi on 23/05/24.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <vector>

// Vector2D class for basic vector operations
class Vector2D {
public:
    float x, y;

    // Constructor
    explicit Vector2D(float x = 0, float y = 0);

    // Suma de 2 vectores
    Vector2D operator+(const Vector2D& other) const;
    // Resta de 2 vectores
    Vector2D operator-(const Vector2D& other) const;
    // Multiplicacion por un escalar
    Vector2D operator*(float scalar) const;
    // Division por un escalar
    Vector2D operator/(float scalar) const;

    // modulo del vector
    float magnitude() const;

    // angulo del vector
    float angle() const;
};

#endif  // VECTOR2D_H
