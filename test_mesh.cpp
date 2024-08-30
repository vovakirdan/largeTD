#include <iostream>
#include "mesh.hpp"
#include "matrix.hpp"

int main() {
    // Define some vertices
    std::vector<Vector3D> vertices = {
        Vector3D(0.0, 0.0, 0.0),
        Vector3D(1.0, 0.0, 0.0),
        Vector3D(0.0, 1.0, 0.0),
        Vector3D(0.0, 0.0, 1.0)
    };

    // Define faces using indices (assuming the vertices define a tetrahedron)
    std::vector<int> indices = {
        0, 1, 2,  // First face
        0, 1, 3,  // Second face
        0, 2, 3,  // Third face
        1, 2, 3   // Fourth face
    };

    // Create a mesh
    Mesh mesh(vertices, indices);

    // Print the initial vertices and faces
    mesh.printVertices();
    mesh.printFaces();

    // Apply a transformation (e.g., scaling)
    Matrix4x4 scalingMatrix = Matrix4x4::scaling(2.0, 2.0, 2.0);
    mesh.transform(scalingMatrix);

    // Print the transformed vertices
    std::cout << "\nAfter scaling:\n";
    mesh.printVertices();

    return 0;
}
