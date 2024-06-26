
#ifndef GAME_ENGINE_MATH_VECTOR2D_H_
#define GAME_ENGINE_MATH_VECTOR2D_H_


namespace engine {
// Vector2D class for basic vector operations
class Vector2D {

public:
    int x, y;

    // Constructor
    explicit Vector2D(int x, int y);
    explicit Vector2D(int a);

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
    // Incrementar vector con un escalar
    Vector2D& operator+=(int scalar);
};
}  // namespace engine

#endif  // GAME_ENGINE_MATH_VECTOR2D_H_
