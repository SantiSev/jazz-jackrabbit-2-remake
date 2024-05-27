//
// Created by santi on 23/05/24.
//

#ifndef GAME_ENGINE_MATH_VECTOR2D_H_
#define GAME_ENGINE_MATH_VECTOR2D_H_

#include <cmath>
#include <vector>

// Vector2D class for basic vector operations
class Vector2D {

private:
    float x, y;

public:
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
    // Redefinir un vector
    Vector2D& operator=(const Vector2D& other);

    // modulo del vector
    float magnitude() const;

    // angulo del vector
    float angle() const;

    float get_x() const { return x; }
    float get_y() const { return y; }

    void set_x(float x) { this->x = x; }
    void set_y(float y) { this->y = y; }

    void setVector(float x, float y);
};

#endif  // GAME_ENGINE_MATH_VECTOR2D_H_
// Copyriht 2024  S.E.V
