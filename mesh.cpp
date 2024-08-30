#include "mesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

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

// Translate the entire mesh
void Mesh::translate(double tx, double ty, double tz) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(tx, ty, tz);
    transform(translationMatrix);  // Apply translation to the entire mesh
}

// Rotate the mesh around the X-axis
void Mesh::rotateX(double angle) {
    Matrix4x4 rotationMatrix = Matrix4x4::rotationX(angle);
    transform(rotationMatrix);  // Apply rotation around X-axis to the entire mesh
}

// Rotate the mesh around the Y-axis
void Mesh::rotateY(double angle) {
    Matrix4x4 rotationMatrix = Matrix4x4::rotationY(angle);
    transform(rotationMatrix);  // Apply rotation around Y-axis to the entire mesh
}

// Rotate the mesh around the Z-axis
void Mesh::rotateZ(double angle) {
    Matrix4x4 rotationMatrix = Matrix4x4::rotationZ(angle);
    transform(rotationMatrix);  // Apply rotation around Z-axis to the entire mesh
}

// Scale the entire mesh
void Mesh::scale(double sx, double sy, double sz) {
    Matrix4x4 scalingMatrix = Matrix4x4::scaling(sx, sy, sz);
    transform(scalingMatrix);  // Apply scaling to the entire mesh
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

bool Mesh::loadFromOBJ(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    vertices.clear();
    indices.clear();
    normals.clear();
    texCoords.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            double x, y, z;
            ss >> x >> y >> z;
            vertices.push_back(Vector3D(x, y, z));
        } else if (type == "vn") {
            double x, y, z;
            ss >> x >> y >> z;
            normals.push_back(Vector3D(x, y, z));
        } else if (type == "vt") {
            double u, v;
            ss >> u >> v;
            texCoords.push_back({u, v});
        } else if (type == "f") {
            int i1, i2, i3;
            char slash;
            ss >> i1 >> slash >> i2 >> slash >> i3;
            indices.push_back(i1 - 1);
            indices.push_back(i2 - 1);
            indices.push_back(i3 - 1);
        }
    }

    file.close();
    return true;
}

bool Mesh::saveToOBJ(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    for (const auto& vertex : vertices) {
        file << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    for (const auto& normal : normals) {
        file << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";
    }

    for (const auto& texCoord : texCoords) {
        file << "vt " << texCoord.first << " " << texCoord.second << "\n";
    }

    for (size_t i = 0; i < indices.size(); i += 3) {
        file << "f " << (indices[i] + 1) << "//" << (indices[i] + 1) << " "
             << (indices[i+1] + 1) << "//" << (indices[i+1] + 1) << " "
             << (indices[i+2] + 1) << "//" << (indices[i+2] + 1) << "\n";
    }

    file.close();
    return true;
}

// This method reverses the direction of all normals in the mesh.
void Mesh::flipNormals() {
    for (auto& normal : normals) {
        normal = normal * -1.0;
    }
}

// This method merges vertices that are closer than a given epsilon (used to avoid duplicate vertices that are nearly identical).
void Mesh::mergeVertices(double epsilon) {
    std::vector<int> remap(vertices.size());
    std::vector<Vector3D> uniqueVertices;

    for (size_t i = 0; i < vertices.size(); ++i) {
        bool merged = false;
        for (size_t j = 0; j < uniqueVertices.size(); ++j) {
            if ((vertices[i] - uniqueVertices[j]).magnitude() < epsilon) {
                remap[i] = j;
                merged = true;
                break;
            }
        }
        if (!merged) {
            remap[i] = uniqueVertices.size();
            uniqueVertices.push_back(vertices[i]);
        }
    }

    vertices = uniqueVertices;

    for (auto& index : indices) {
        index = remap[index];
    }
}
