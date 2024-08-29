#include "matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

// Default constructor - Identity matrix
Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

// Parameterized constructor
Matrix4x4::Matrix4x4(double matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = matrix[i][j];
        }
    }
}

// Helper method to calculate the minor matrix determinant
double Matrix4x4::minor(int r, int c) const {
    double subMatrix[3][3];
    int subRow = 0, subCol = 0;

    for (int i = 0; i < 4; i++) {
        if (i == r) continue;
        subCol = 0;
        for (int j = 0; j < 4; j++) {
            if (j == c) continue;
            subMatrix[subRow][subCol] = m[i][j];
            subCol++;
        }
        subRow++;
    }

    return subMatrix[0][0] * (subMatrix[1][1] * subMatrix[2][2] - subMatrix[1][2] * subMatrix[2][1])
         - subMatrix[0][1] * (subMatrix[1][0] * subMatrix[2][2] - subMatrix[1][2] * subMatrix[2][0])
         + subMatrix[0][2] * (subMatrix[1][0] * subMatrix[2][1] - subMatrix[1][1] * subMatrix[2][0]);
}

// Helper method to calculate the determinant of a 4x4 matrix
double Matrix4x4::determinant() const {
    double det = 0.0;
    for (int j = 0; j < 4; j++) {
        det += (j % 2 == 0 ? 1 : -1) * m[0][j] * minor(0, j);
    }
    return det;
}

// Addition of matrices
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][j] + mat.m[i][j];
        }
    }
    return result;
}

// Subtraction of matrices
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][j] - mat.m[i][j];
        }
    }
    return result;
}

// Multiplication of matrices
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * mat.m[k][j];
            }
        }
    }
    return result;
}

// Matrix * Vector multiplication (assuming a 4D vector)
double* Matrix4x4::operator*(const double vec[4]) const {
    static double result[4];
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += m[i][j] * vec[j];
        }
    }
    return result;
}

// Matrix * Vector3D multiplication
Vector3D Matrix4x4::operator*(const Vector3D& vec) const {
    double result[4];
    double vec4[4] = { vec.x, vec.y, vec.z, 1.0 }; // Convert Vector3D to homogeneous coordinates

    for (int i = 0; i < 4; i++) {
        result[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            result[i] += m[i][j] * vec4[j];
        }
    }

    return Vector3D(result[0], result[1], result[2]); // Return transformed Vector3D
}

// Transpose of the matrix
Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}

// Method to calculate the inverse of the matrix
Matrix4x4 Matrix4x4::inverse() const {
    Matrix4x4 result;
    double det = determinant();

    if (det == 0) {
        std::cerr << "Matrix is singular, cannot compute inverse." << std::endl;
        return result;  // Return identity matrix if non-invertible
    }

    double invDet = 1.0 / det;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double cofactor = ((i + j) % 2 == 0 ? 1 : -1) * minor(i, j);
            result.m[j][i] = invDet * cofactor;  // Transpose step is combined here
        }
    }

    return result;
}

// Print the matrix
void Matrix4x4::print() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << std::setw(10) << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Static method for creating a translation matrix
Matrix4x4 Matrix4x4::translation(double tx, double ty, double tz) {
    Matrix4x4 result;
    result.m[0][3] = tx;
    result.m[1][3] = ty;
    result.m[2][3] = tz;
    return result;
}

// Static method for creating a scaling matrix
Matrix4x4 Matrix4x4::scaling(double sx, double sy, double sz) {
    Matrix4x4 result;
    result.m[0][0] = sx;
    result.m[1][1] = sy;
    result.m[2][2] = sz;
    return result;
}

// Static method for creating a rotation matrix around the X-axis
Matrix4x4 Matrix4x4::rotationX(double angle) {
    Matrix4x4 result;
    double rad = angle * M_PI / 180.0;
    result.m[1][1] = cos(rad);
    result.m[1][2] = -sin(rad);
    result.m[2][1] = sin(rad);
    result.m[2][2] = cos(rad);
    return result;
}

// Static method for creating a rotation matrix around the Y-axis
Matrix4x4 Matrix4x4::rotationY(double angle) {
    Matrix4x4 result;
    double rad = angle * M_PI / 180.0;
    result.m[0][0] = cos(rad);
    result.m[0][2] = sin(rad);
    result.m[2][0] = -sin(rad);
    result.m[2][2] = cos(rad);
    return result;
}

// Static method for creating a rotation matrix around the Z-axis
Matrix4x4 Matrix4x4::rotationZ(double angle) {
    Matrix4x4 result;
    double rad = angle * M_PI / 180.0;
    result.m[0][0] = cos(rad);
    result.m[0][1] = -sin(rad);
    result.m[1][0] = sin(rad);
    result.m[1][1] = cos(rad);
    return result;
}

