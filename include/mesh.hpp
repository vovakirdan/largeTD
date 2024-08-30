#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "vector3d.hpp"
#include "matrix.hpp"
#include "Config.hpp"

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
    void translate(double tx, double ty, double tz);   // Translate the entire mesh
    void rotateX(double angle);                        // Rotate the mesh around the X-axis
    void rotateY(double angle);                        // Rotate the mesh around the Y-axis
    void rotateZ(double angle);                        // Rotate the mesh around the Z-axis
    void scale(double sx, double sy, double sz);       // Scale the entire mesh

    void printVertices() const;                   // Print all vertices
    void printFaces() const;                      // Print all faces (indices)
    void printNormals() const;                          // Print all normals
    void printTexCoords() const;                        // Print all texture coordinates

    // File I/O methods
    bool loadFromOBJ(const std::string& filename);    // Load a mesh from an OBJ file
    bool saveToOBJ(const std::string& filename) const; // Save the mesh to an OBJ file

    // Manipulation methods
    void flipNormals();                               // Flip the direction of the normals
    void mergeVertices(double epsilon = Config::instance().getEpsilonMergeVertices());        // Merge vertices that are close together
    void smooth(double factor = Config::instance().getSmoothFactor());                           // Smooth the mesh
    void subdivideSurface();                                    // Subdivide the surface for more detail
    Mesh booleanUnion(const Mesh& other) const;                 // Union of two meshes
    // todo implement it
    Mesh booleanIntersection(const Mesh& other) const;          // Intersection of two meshes
    Mesh booleanDifference(const Mesh& other) const;            // Difference between two meshes
};

#endif // MESH_HPP
