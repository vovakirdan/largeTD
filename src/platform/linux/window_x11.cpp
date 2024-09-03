#include "window_x11.hpp"
#include <X11/Xutil.h>
#include <iostream>

WindowX11::WindowX11(int width, int height, const std::string& title)
    : CustomWindow(width, height, title), display(nullptr) {  // Replace Window with CustomWindow
    // No need to initialize platformWindow here, it will be done in initialize()
}

WindowX11::~WindowX11() {
    cleanup();
}

void WindowX11::initialize() {
    display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Cannot open display\n";
        return;
    }

    int screen = DefaultScreen(display);
    platformWindow = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1,
                                         BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, platformWindow, ExposureMask | KeyPressMask);
    XMapWindow(display, platformWindow);
}

void WindowX11::cleanup() {
    if (platformWindow) {
        XDestroyWindow(display, platformWindow);
        XCloseDisplay(display);
        platformWindow = 0;
        display = nullptr;
    }
}

void WindowX11::mainLoop() {
    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Handle window exposure, e.g., redraw window
        }
        if (event.type == KeyPress) {
            break;
        }
    }
}

void WindowX11::present(Framebuffer& framebuffer) {
    // TODO: Implement framebuffer drawing for X11 (or use shared memory)
}
