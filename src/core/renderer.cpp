#include "renderer.hpp"
#include <algorithm>

Renderer::Renderer(Mesh* mesh, Camera* camera, Viewport* viewport, Framebuffer* framebuffer, uint32_t backgroundColor)
    : mesh(mesh), camera(camera), viewport(viewport), framebuffer(framebuffer), backgroundColor(backgroundColor) {}

void Renderer::setMesh(Mesh* newMesh) {
    mesh = newMesh;
}

void Renderer::setCamera(Camera* newCamera) {
    camera = newCamera;
}

void Renderer::setViewport(Viewport* newViewport) {
    viewport = newViewport;
}

void Renderer::setFramebuffer(Framebuffer* newFramebuffer) {
    framebuffer = newFramebuffer;
}

void Renderer::render() {
    framebuffer->clear(backgroundColor);

    Matrix4x4 viewMatrix = camera->getViewMatrix();
    Matrix4x4 projectionMatrix = camera->getProjectionMatrix();

    std::vector<Vector3D> transformedVertices;
    for (const Vector3D& vertex : mesh->getVertices()) {
        Vector3D viewVertex = vertex.transform(viewMatrix);
        Vector3D clipVertex = viewVertex.transform(projectionMatrix);
        clipVertex.x /= clipVertex.z;
        clipVertex.y /= clipVertex.z;
        clipVertex.z /= clipVertex.z;
        Vector3D screenVertex = viewport->applyViewportTransformation(clipVertex);
        transformedVertices.push_back(screenVertex);
    }

    const std::vector<int>& indices = mesh->getIndices();
    for (size_t i = 0; i < indices.size(); i += 3) {
        drawTriangle(transformedVertices[indices[i]],
                     transformedVertices[indices[i + 1]],
                     transformedVertices[indices[i + 2]],
                     Config::instance().getDefaultMeshColor());
    }
}

void Renderer::drawTriangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2, uint32_t color) {
    int minX = std::min({v0.x, v1.x, v2.x});
    int minY = std::min({v0.y, v1.y, v2.y});
    int maxX = std::max({v0.x, v1.x, v2.x});
    int maxY = std::max({v0.y, v1.y, v2.y});

    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, framebuffer->getWidth() - 1);
    maxY = std::min(maxY, framebuffer->getHeight() - 1);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            Vector3D p(x, y, 0);
            Vector3D v0v1 = v1 - v0;
            Vector3D v0v2 = v2 - v0;
            Vector3D v0p = p - v0;

            double d00 = v0v1.dot(v0v1);
            double d01 = v0v1.dot(v0v2);
            double d11 = v0v2.dot(v0v2);
            double d20 = v0p.dot(v0v1);
            double d21 = v0p.dot(v0v2);
            double denom = d00 * d11 - d01 * d01;

            double v = (d11 * d20 - d01 * d21) / denom;
            double w = (d00 * d21 - d01 * d20) / denom;
            double u = 1.0 - v - w;

            if (u >= 0 && v >= 0 && w >= 0) {
                framebuffer->setPixel(x, y, color);
            }
        }
    }
}
