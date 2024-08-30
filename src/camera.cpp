#include "camera.hpp"
#include <cmath>

Camera::Camera(const Vector3D& position, const Vector3D& target, const Vector3D& up)
    : position(position), target(target), up(up) {
    updateViewMatrix();  // Initialize the view matrix based on the initial position and target
}

void Camera::setPerspective(double fov, double aspect, double near, double far) {
    projectionMatrix = Matrix4x4::perspective(fov, aspect, near, far);
}

void Camera::setOrthographic(double left, double right, double bottom, double top, double near, double far) {
    projectionMatrix = Matrix4x4::orthographic(left, right, bottom, top, near, far);
}

Matrix4x4 Camera::getViewMatrix() const {
    return viewMatrix;
}

Matrix4x4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::moveTo(const Vector3D& newPosition) {
    position = newPosition;
    updateViewMatrix();  // Recalculate the view matrix with the new position
}

void Camera::lookAt(const Vector3D& newTarget) {
    target = newTarget;
    updateViewMatrix();  // Recalculate the view matrix with the new target
}

void Camera::updateViewMatrix() {
    Vector3D zAxis = (position - target).normalize();
    Vector3D xAxis = up.cross(zAxis).normalize();
    Vector3D yAxis = zAxis.cross(xAxis).normalize();

    viewMatrix = Matrix4x4();
    viewMatrix.m[0][0] = xAxis.x; viewMatrix.m[0][1] = xAxis.y; viewMatrix.m[0][2] = xAxis.z; viewMatrix.m[0][3] = -xAxis.dot(position);
    viewMatrix.m[1][0] = yAxis.x; viewMatrix.m[1][1] = yAxis.y; viewMatrix.m[1][2] = yAxis.z; viewMatrix.m[1][3] = -yAxis.dot(position);
    viewMatrix.m[2][0] = zAxis.x; viewMatrix.m[2][1] = zAxis.y; viewMatrix.m[2][2] = zAxis.z; viewMatrix.m[2][3] = -zAxis.dot(position);
    viewMatrix.m[3][0] = 0.0;     viewMatrix.m[3][1] = 0.0;     viewMatrix.m[3][2] = 0.0;     viewMatrix.m[3][3] = 1.0;
}
