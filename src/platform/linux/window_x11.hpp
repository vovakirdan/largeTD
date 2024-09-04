#ifndef WINDOW_X11_HPP
#define WINDOW_X11_HPP

#include "../../ui/window.hpp"
#ifdef __unix__
#include <X11/Xlib.h> // Include X11 library to define Display

class WindowX11 : public CustomWindow {
public:
    WindowX11(int width, int height, const std::string& title);
    ~WindowX11() override;

    void initialize() override;
    void cleanup() override;
    void mainLoop() override;
    void present(Framebuffer& framebuffer) override;

private:
    Display* display;  // Handle to the X server
};

#endif
#endif // WINDOW_X11_HPP
