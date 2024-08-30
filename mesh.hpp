#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "vector3d.hpp"
#include "matrix.hpp"

class Mesh {
private:
    std::vector<Vector3D> vertices;        // List of vertices
    std::vector<int> indices;              // List of indices defining faces (optional)
    std::vector<Vector3D> normals;
    std::vector<std::pair<double, double>> texCoords;

public:
    Mesh();                                // Default constructor
    Mesh(const std::vector<Vector3D>& vertices);    // Constructor with vertices only
    Mesh(const std::vector<Vector3D>& vertices, const std::vector<int>& indices); // Constructor with vertices and indices

    void addVertex(const Vector3D& vertex);       // Add a single vertex
    void addFace(int i1, int i2, int i3);         // Add a face using 3 vertex indices
    void addNormal(const Vector3D& normal);       // Add a single normal
    void addTexCoord(double u, double v);         // Add a texture coordinates

    void transform(const Matrix4x4& matrix);      // Transform the entire mesh
    void merge(const Mesh& other);
    void subdivideFaces();

    void printVertices() const;                   // Print all vertices
    void printFaces() const;                      // Print all faces (indices)
    void printNormals() const;                          // Print all normals
    void printTexCoords() const;                        // Print all texture coordinates
};

#endif // MESH_HPP
