#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "framebuffer.hpp"

// class Framebuffer; // Forward declaration of Framebuffer class

class Window {
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();

    virtual void initialize() = 0;
    virtual void cleanup() = 0;
    virtual void mainLoop() = 0;
    virtual void present(Framebuffer& framebuffer) = 0;

    int getWidth() const;
    int getHeight() const;

protected:
    int width;
    int height;
    std::string title;

    // Use the correct type for platform-specific window handles
    #ifdef _WIN32
        HWND platformWindow;
    #elif defined(__unix__)
        unsigned long platformWindow;  // Corresponds to X11's Window type
    #endif
};

#endif // WINDOW_HPP
