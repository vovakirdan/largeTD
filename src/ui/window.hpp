#ifndef CUSTOM_WINDOW_HPP
#define CUSTOM_WINDOW_HPP

#include <string>

class Framebuffer; // Forward declaration of Framebuffer class

class CustomWindow {
public:
    CustomWindow(int width, int height, const std::string& title);
    virtual ~CustomWindow();

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

#ifdef _WIN32
    HWND platformWindow;
#elif defined(__unix__)
    unsigned long platformWindow;  // Corresponds to X11's Window type
#endif
};

#endif // CUSTOM_WINDOW_HPP
