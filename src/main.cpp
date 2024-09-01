#include "core/camera.hpp"
#include "core/mesh.hpp"
#include "core/viewport.hpp"
#include "core/vector3d.hpp"
#include "core/matrix.hpp"

int main() {
    // Initialize the camera at (0, 0, 10), looking at the origin (0, 0, 0), with up direction (0, 1, 0)
    Camera camera(Vector3D(0, 0, 10), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    camera.setPerspective(90.0 * 3.14 / 180.0, 16.0 / 9.0, 0.1, 100.0);

    // Initialize the viewport with screen dimensions
    Viewport viewport(800, 600);

    // A sample 3D point in world space
    Vector3D pointInWorldSpace(1.0, 1.0, 1.0);

    // Apply view and projection transformations
    Matrix4x4 viewMatrix = camera.getViewMatrix();
    Matrix4x4 projectionMatrix = camera.getProjectionMatrix();

    // Transform the point to camera space
    Vector3D pointInCameraSpace = pointInWorldSpace.transform(viewMatrix);

    // Transform the point to clip space
    Vector3D pointInClipSpace = pointInCameraSpace.transform(projectionMatrix);

    // Apply the viewport transformation to get screen coordinates
    Vector3D pointOnScreen = viewport.applyViewportTransformation(pointInClipSpace);

    // Print the screen coordinates
    std::cout << "Screen coordinates: (" << pointOnScreen.x << ", " << pointOnScreen.y << ")" << std::endl;

    return 0;
}
