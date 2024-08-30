#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include "vector3d.hpp"
#include <iostream>

class Matrix4x4 {
private:
    double minor(int r, int c) const;
    double determinant() const;

public:
    double m[4][4];
    Matrix4x4();
    Matrix4x4(double matrix[4][4]);
    Matrix4x4 operator+(const Matrix4x4& mat) const;
    Matrix4x4 operator-(const Matrix4x4& mat) const;
    Matrix4x4 operator*(const Matrix4x4& mat) const;
    double* operator*(const double vec[4]) const;
    Matrix4x4 inverse() const;
    Matrix4x4 transpose() const;

    Vector3D operator*(const Vector3D& vec) const;

    void print() const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix);

    static Matrix4x4 translation(double tx, double ty, double tz);
    static Matrix4x4 scaling(double sx, double sy, double sz);
    static Matrix4x4 rotationX(double angle);
    static Matrix4x4 rotationY(double angle);
    static Matrix4x4 rotationZ(double angle);
    static Matrix4x4 perspective(double fov, double aspect, double near, double far);
    static Matrix4x4 orthographic(double left, double right, double bottom, double top, double near, double far);
};

#endif // MATRIX4x4_HPP