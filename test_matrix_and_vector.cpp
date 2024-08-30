#include <iostream>
#include "matrix.hpp"
#include "vector3d.hpp"

int main() {
    Vector3D v1(1.0, 2.0, 3.0);

    // Translation matrix
    Matrix4x4 translationMatrix = Matrix4x4::translation(10.0, 0.0, 0.0);
    Vector3D translatedV1 = v1.transform(translationMatrix);

    std::cout << "Original Vector: ";
    v1.print();

    std::cout << "Translated Vector: ";
    translatedV1.print();

    // Rotation matrix around Z axis
    Matrix4x4 rotationMatrix = Matrix4x4::rotationZ(90.0);  // 90 degrees rotation
    Vector3D rotatedV1 = v1.transform(rotationMatrix);

    std::cout << "Rotated Vector: " << rotatedV1 << std::endl;

    // Define parameters for orthographic projection
    double left = -10.0;
    double right = 10.0;
    double bottom = -10.0;
    double top = 10.0;
    double near = 0.1;
    double far = 100.0;

    // Create orthographic projection matrix
    Matrix4x4 orthoMatrix = Matrix4x4::orthographic(left, right, bottom, top, near, far);
    std::cout << orthoMatrix;

    // Test transforming a vector using the orthographic matrix
    Vector3D orthoPoint(5.0, 5.0, -10.0);
    Vector3D transformedOrthoPoint = orthoPoint.transform(orthoMatrix);

    std::cout << "Transformed Orthographic Point: " << transformedOrthoPoint << std::endl;

    // Define parameters for perspective projection
    double fov = 90.0 * 3.14 / 180.0;  // Convert degrees to radians
    double aspect = 16.0 / 9.0;

    // Create perspective projection matrix
    Matrix4x4 perspectiveMatrix = Matrix4x4::perspective(fov, aspect, near, far);
    std::cout << perspectiveMatrix;

    // Test transforming a vector using the perspective matrix
    Vector3D point(1.0, 1.0, -5.0);
    Vector3D transformedPoint = point.transform(perspectiveMatrix);

    std::cout << "Transformed Point: " << transformedPoint;

    return 0;
}
