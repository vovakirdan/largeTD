#include "camera.hpp"
#include "mesh.hpp"
#include "vector3d.hpp"
#include "matrix.hpp"
#include "Config.hpp"

void testCamera() {
    // Initialize the camera at (0, 0, 10), looking at the origin (0, 0, 0), with up direction (0, 1, 0)
    Camera camera(Vector3D(0, 0, 10), Vector3D(0, 0, 0), Vector3D(0, 1, 0));

    // Set perspective projection with FOV 90 degrees, aspect ratio 16:9, near plane 0.1, far plane 100
    camera.setPerspective(90.0 * Config::instance().getPI() / 180.0, 16.0 / 9.0, 0.1, 100.0);

    // Or set orthographic projection
    // camera.setOrthographic(-10, 10, -10, 10, 0.1, 100.0);

    // Move the camera
    camera.moveTo(Vector3D(5, 5, 10));

    // Change the camera's target
    camera.lookAt(Vector3D(0, 0, 0));

    // Use the view and projection matrices for rendering
    Matrix4x4 viewMatrix = camera.getViewMatrix();
    Matrix4x4 projectionMatrix = camera.getProjectionMatrix();
}
