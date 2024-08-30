#include "mesh.hpp"
#include <iostream>

// Default constructor
Mesh::Mesh() {}

// Constructor with vertices only
Mesh::Mesh(const std::vector<Vector3D>& vertices)
    : vertices(vertices) {}

// Constructor with vertices and indices
Mesh::Mesh(const std::vector<Vector3D>& vertices, const std::vector<int>& indices)
    : vertices(vertices), indices(indices) {}

// Add a single vertex
void Mesh::addVertex(const Vector3D& vertex) {
    vertices.push_back(vertex);
}

// Add a face using 3 vertex indices
void Mesh::addFace(int i1, int i2, int i3) {
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

// Add a single normal
void Mesh::addNormal(const Vector3D& normal) {
    normals.push_back(normal);
}

// Add a texture coordinates
void Mesh::addTexCoord(double u, double v) {
    texCoords.push_back({u, v});
}

// Transform the entire mesh
void Mesh::transform(const Matrix4x4& matrix) {
    for (auto& vertex : vertices) {
        vertex = vertex.transform(matrix);
    }
}

// Merge another mesh into this one
void Mesh::merge(const Mesh& other) {
    // Offset for indices
    int indexOffset = vertices.size();

    // Add vertices, normals, and texture coordinates from the other mesh
    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());
    normals.insert(normals.end(), other.normals.begin(), other.normals.end());
    texCoords.insert(texCoords.end(), other.texCoords.begin(), other.texCoords.end());

    // Add indices, adjusting for the index offset
    for (int index : other.indices) {
        indices.push_back(index + indexOffset);
    }
}

// Subdivide each face into smaller triangles
void Mesh::subdivideFaces() {
    std::vector<int> newIndices;
    for (size_t i = 0; i < indices.size(); i += 3) {
        int i1 = indices[i];
        int i2 = indices[i + 1];
        int i3 = indices[i + 2];

        // Create midpoints
        Vector3D v1 = vertices[i1];
        Vector3D v2 = vertices[i2];
        Vector3D v3 = vertices[i3];
        
        Vector3D m12 = (v1 + v2) * 0.5;
        Vector3D m23 = (v2 + v3) * 0.5;
        Vector3D m31 = (v3 + v1) * 0.5;

        int m12Index = vertices.size();
        int m23Index = m12Index + 1;
        int m31Index = m23Index + 1;

        vertices.push_back(m12);
        vertices.push_back(m23);
        vertices.push_back(m31);

        // Define new faces
        newIndices.push_back(i1); newIndices.push_back(m12Index); newIndices.push_back(m31Index);
        newIndices.push_back(m12Index); newIndices.push_back(i2); newIndices.push_back(m23Index);
        newIndices.push_back(m31Index); newIndices.push_back(m23Index); newIndices.push_back(i3);
        newIndices.push_back(m12Index); newIndices.push_back(m23Index); newIndices.push_back(m31Index);
    }
    indices = newIndices;
}


// Print all vertices
void Mesh::printVertices() const {
    std::cout << "Vertices:\n";
    for (const auto& vertex : vertices) {
        vertex.print();
    }
}

// Print all faces (indices)
void Mesh::printFaces() const {
    if (indices.empty()) {
        std::cout << "No faces defined.\n";
        return;
    }

    std::cout << "Faces:\n";
    for (size_t i = 0; i < indices.size(); i += 3) {
        std::cout << "(" << indices[i] << ", " << indices[i+1] << ", " << indices[i+2] << ")\n";
    }
}

void Mesh::printNormals() const {
    std::cout << "Normals:\n";
    for (const auto& normal : normals) {
        normal.print();
    }
}

void Mesh::printTexCoords() const {
    std::cout << "Texture Coordinates:\n";
    for (const auto& texCoord : texCoords) {
        std::cout << "(" << texCoord.first << ", " << texCoord.second << ")\n";
    }
}
