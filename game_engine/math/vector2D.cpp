
#include "vector2D.h"

// Constructor de la clase Vector2D
Vector2D::Vector2D(int x, int y): x(x), y(y) {}

// Constructor de la clase Vector2D
Vector2D::Vector2D(int a): x(a), y(a) {}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(this->x - other.x, this->y - other.y);
}

Vector2D Vector2D::operator*(int scalar) const {
    return Vector2D(this->x * scalar, this->y * scalar);
}

Vector2D Vector2D::operator/(int scalar) const {
    return Vector2D(this->x / scalar, this->y / scalar);
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

bool Vector2D::operator==(const Vector2D& other) const {
    return this->x == other.x && this->y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return this->x != other.x || this->y != other.y;
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
