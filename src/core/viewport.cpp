#include "viewport.hpp"

Viewport::Viewport(int width, int height)
    : width(width), height(height), aspectRatio(static_cast<double>(width) / height) {}

void Viewport::updateDimensions(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    aspectRatio = static_cast<double>(width) / height;
}

Vector3D Viewport::convertToScreenCoordinates(const Vector3D& ndcCoords) const {
    double x = (ndcCoords.x + 1.0) * 0.5 * width;
    double y = (1.0 - ndcCoords.y) * 0.5 * height;  // Invert y-axis for screen coordinates
    return Vector3D(x, y, ndcCoords.z);  // z remains the same for depth buffer use
}

Vector3D Viewport::applyViewportTransformation(const Vector3D& clipCoords) const {
    // Perspective divide to get normalized device coordinates (NDC)
    Vector3D ndcCoords = Vector3D(
        clipCoords.x / clipCoords.z,
        clipCoords.y / clipCoords.z,
        clipCoords.z
    );

    // Convert NDC to screen coordinates
    return convertToScreenCoordinates(ndcCoords);
}
