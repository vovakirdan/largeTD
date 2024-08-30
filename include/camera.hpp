#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "matrix.hpp"
#include "vector3d.hpp"

class Camera {
private:
    Vector3D position;         // Camera position in world space
    Vector3D target;           // Target point the camera is looking at
    Vector3D up;               // Up direction for the camera

    Matrix4x4 viewMatrix;      // View (camera) matrix
    Matrix4x4 projectionMatrix; // Projection matrix (perspective or orthographic)

public:
    // Constructor
    Camera(const Vector3D& position, const Vector3D& target, const Vector3D& up);

    // Set the perspective projection
    void setPerspective(double fov, double aspect, double near, double far);

    // Set the orthographic projection
    void setOrthographic(double left, double right, double bottom, double top, double near, double far);

    // Get the view matrix
    Matrix4x4 getViewMatrix() const;

    // Get the projection matrix
    Matrix4x4 getProjectionMatrix() const;

    // Move the camera to a new position
    void moveTo(const Vector3D& newPosition);

    // Look at a new target point
    void lookAt(const Vector3D& newTarget);

    // Update the view matrix (must be called after moving or changing the target)
    void updateViewMatrix();
};

#endif // CAMERA_HPP
