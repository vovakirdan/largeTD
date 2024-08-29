#include "vector3d.hpp"
#include "matrix.hpp"
#include <iostream>
#include <cmath>

// Default constructor
Vector3D::Vector3D() : x(0), y(0), z(0) {}

// Parameterized constructor
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

// Addition
Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

// Subtraction
Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}
// Vector * double
Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

// Double * Vector
Vector3D operator*(double scalar, const Vector3D& vec) {
    return Vector3D(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

// Dot product
double Vector3D::dot(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Cross product
Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

// Magnitude
double Vector3D::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize
Vector3D Vector3D::normalize() const {
    double mag = magnitude();
    if (mag == 0) return Vector3D(0, 0, 0); // Avoid division by zero
    return Vector3D(x / mag, y / mag, z / mag);
}

// Print vector
void Vector3D::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

Vector3D Vector3D::transform(const Matrix4x4& matrix) const {
    return matrix * (*this);
}
