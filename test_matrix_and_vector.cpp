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

    return 0;
}
