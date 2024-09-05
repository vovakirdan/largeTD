#include <iostream>
#include "core/camera.hpp"
#include "core/framebuffer.hpp"
#include "core/matrix.hpp"
#include "core/mesh.hpp"
#include "core/renderer.hpp"
#include "core/vector3d.hpp"
#include "core/viewport.hpp"
#include "platform/windows/window_winapi.hpp"  // Include appropriate platform header
#include "platform/linux/window_x11.hpp"
#include "ui/event_handler.hpp"
#include "ui/ui_manager.hpp"
#include "ui/ui_renderer.hpp"
#include "core/Config.hpp"

// Platform-dependent includes
#ifdef _WIN32
#include "platform/windows/window_winapi.hpp"
#elif __linux__
#include "platform/linux/window_x11.hpp"
#endif

int main() {
    // Initialize configuration
    Config& config = Config::instance();

    // Initialize platform-specific window
    CustomWindow* window;
#ifdef _WIN32
    window = new WindowWinAPI(800, 600, "3D Renderer");
#elif __linux__
    window = new WindowX11(800, 600, "3D Renderer");
#endif

    // if (!window->initialize()) {
    //     std::cerr << "Failed to initialize the window." << std::endl;
    //     return -1;
    // }

    // Create and set up the camera
    Vector3D cameraPosition(0.0, 0.0, 5.0);
    Vector3D cameraTarget(0.0, 0.0, 0.0);
    Vector3D cameraUp(0.0, 1.0, 0.0);
    Camera camera(cameraPosition, cameraTarget, cameraUp);
    camera.setPerspective(45.0, window->getWidth() / (float)window->getHeight(), 0.1, 100.0);

    // Create the framebuffer and viewport
    Framebuffer framebuffer(window->getWidth(), window->getHeight());
    Viewport viewport(window->getWidth(), window->getHeight());

    // Load or create the mesh
    Mesh mesh;
    if (!mesh.loadFromOBJ("H:\\large3d\\models\\airboat.obj")) { // Provide a path to an OBJ file
        std::cerr << "Failed to load mesh from OBJ file." << std::endl;
        return -1;
    }

    // Initialize the renderer
    Renderer renderer(&mesh, &camera, &viewport, &framebuffer);

    // Set up the UI Renderer and UI Manager
    UIRenderer uiRenderer(&framebuffer);
    UIManager uiManager(&uiRenderer);

    // Example UI Component: a simple button
    UIButton button(10, 10, 100, 30, 0xFF00FF00); // Green button
    uiManager.addComponent(&button);

    // Event Handler
    EventHandler eventHandler;

    // Main loop
    window->mainLoop([&]() {
        // Poll events
        eventHandler.pollEvents();

        // Update camera or other scene components

        // Clear the framebuffer
        framebuffer.clear(config.getFramebufferDefaultColor());

        // Render the mesh
        renderer.render();

        // Render the UI
        uiManager.renderUI();

        // Present the rendered frame
        window->present(framebuffer);
        });

    // Cleanup is handled by destructors
    window->cleanup();
    delete window;

    return 0;
}
