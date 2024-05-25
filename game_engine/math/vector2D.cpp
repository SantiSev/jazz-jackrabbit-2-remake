
#include "vector2D.h"

// Constructor de la clase Vector2D
Vector2D::Vector2D(float x, float y): x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(this->x - other.x, this->y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(this->x * scalar, this->y * scalar);
}

Vector2D Vector2D::operator/(float scalar) const {
    return Vector2D(this->x / scalar, this->y / scalar);
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}


float Vector2D::magnitude() const { return std::sqrt(x * x + y * y); }

float Vector2D::angle() const { return std::atan2(y, x); }
