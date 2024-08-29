#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>

class Matrix4x4;

class Vector3D {
public:
    double x, y, z;
    Vector3D();
    Vector3D(double x, double y, double z);
    Vector3D operator+(const Vector3D& v) const;
    Vector3D operator-(const Vector3D& v) const;
    Vector3D operator*(double scalar) const;
    friend Vector3D operator*(double scalar, const Vector3D& vec);
    double dot(const Vector3D& v) const;
    Vector3D cross(const Vector3D& v) const;
    double magnitude() const;
    Vector3D normalize() const;
    void print() const;
    // '<<' overload
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    Vector3D transform(const Matrix4x4& matrix) const;
};

#endif // VECTOR3d_HPP