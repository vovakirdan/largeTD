#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "mesh.hpp"
#include "camera.hpp"
#include "viewport.hpp"
#include "framebuffer.hpp"
#include "Config.hpp"

class Renderer {
private:
    Mesh* mesh;
    Camera* camera;
    Viewport* viewport;
    Framebuffer* framebuffer;
    uint32_t backgroundColor;

public:
    Renderer(Mesh* mesh, Camera* camera, Viewport* viewport, Framebuffer* framebuffer, uint32_t backgroundColor = Config::instance().getFramebufferDefaultColor());

    void setMesh(Mesh* newMesh);
    void setCamera(Camera* newCamera);
    void setViewport(Viewport* newViewport);
    void setFramebuffer(Framebuffer* newFramebuffer);
    void render();

private:
    void drawTriangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2, uint32_t color);
};

#endif // RENDERER_HPP
