#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "matrix.hpp"
#include "vector3d.hpp"

class Viewport {
private:
    int width;   // Screen width
    int height;  // Screen height
    double aspectRatio;  // Aspect ratio (width / height)

public:
    // Constructor
    Viewport(int width, int height);

    // Update the viewport dimensions and aspect ratio
    void updateDimensions(int newWidth, int newHeight);

    // Convert from normalized device coordinates (NDC) to screen coordinates
    Vector3D convertToScreenCoordinates(const Vector3D& ndcCoords) const;

    // Apply viewport transformation to a 3D point (after projection and perspective divide)
    Vector3D applyViewportTransformation(const Vector3D& clipCoords) const;
};

#endif // VIEWPORT_HPP
