#include "test_matrix_and_vector.cpp"
#include "test_mesh.cpp"
#include "test_vector3d.cpp"

int main() {
    // Vector 3d
    test_addition();
    test_subtraction();
    test_dot_product();
    test_cross_product();
    test_magnitude();
    test_normalization();

    // Mesh
    testMesh();

    // matrix
    testMatrix();

    return 0;
}