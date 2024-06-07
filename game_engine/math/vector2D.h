//
// Created by santi on 23/05/24.
//

#ifndef GAME_ENGINE_MATH_VECTOR2D_H_
#define GAME_ENGINE_MATH_VECTOR2D_H_

// Vector2D class for basic vector operations
class Vector2D {

public:
    int x, y;

    // Constructor
    explicit Vector2D(int x = 0, int y = 0);

    // Suma de 2 vectores
    Vector2D operator+(const Vector2D& other) const;
    // Resta de 2 vectores
    Vector2D operator-(const Vector2D& other) const;
    // Multiplicacion por un escalar
    Vector2D operator*(int scalar) const;
    // Division por un escalar
    Vector2D operator/(int scalar) const;
    // Redefinir un vector
    Vector2D& operator=(const Vector2D& other);
    // Igualar un vector a otro
    bool operator==(const Vector2D& other) const;
    // Desigualar un vector con otro
    bool operator!=(const Vector2D& other) const;
    // Desincrementar vector
    Vector2D& operator-=(const Vector2D& other);
    // Incrementar vector
    Vector2D& operator+=(const Vector2D& other);
};

#endif  // GAME_ENGINE_MATH_VECTOR2D_H_
// Copyriht 2024  S.E.V
