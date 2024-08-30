#include <iostream>
#include "vector3d.hpp"  // Assuming Vector3D class is in vector3d.cpp

void test_addition() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result = v1 + v2;
    std::cout << "Addition Test: ";
    result.print();  // Expected Output: (5, 7, 9)
}

void test_subtraction() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result = v1 - v2;
    std::cout << "Subtraction Test: ";
    result.print();  // Expected Output: (-3, -3, -3)
}

void test_dot_product() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    double result = v1.dot(v2);
    std::cout << "Dot Product Test: " << result << std::endl;  // Expected Output: 32
}

void test_cross_product() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result = v1.cross(v2);
    std::cout << "Cross Product Test: ";
    result.print();  // Expected Output: (-3, 6, -3)
}

void test_magnitude() {
    Vector3D v1(1.0, 2.0, 3.0);
    double result = v1.magnitude();
    std::cout << "Magnitude Test: " << result << std::endl;  // Expected Output: 3.74166
}

void test_normalization() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D result = v1.normalize();
    std::cout << "Normalization Test: ";
    result.print();  // Expected Output: (0.267261, 0.534522, 0.801784)
}
