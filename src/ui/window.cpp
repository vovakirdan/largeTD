#include "window.hpp"
#include "../core/framebuffer.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#endif

#ifdef _WIN32
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    CustomWindow* window = reinterpret_cast<CustomWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (window) {
        switch (uMsg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CustomWindow::initialize() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "CustomWindowClass";

    RegisterClass(&wc);

    platformWindow = CreateWindowEx(
            0,
            "CustomWindowClass",
            title.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL
    );

    if (platformWindow == NULL) {
        // Handle error
    }

    SetWindowLongPtr(reinterpret_cast<HWND>(platformWindow), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    ShowWindow(reinterpret_cast<HWND>(platformWindow), SW_SHOW);
}

void CustomWindow::cleanup() {
    if (platformWindow) {
        DestroyWindow(reinterpret_cast<HWND>(platformWindow));
        platformWindow = nullptr;
    }
}

void CustomWindow::mainLoop() {
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // todo Run the rendering loop, process input, update the scene, etc.
        }
    }
}

void CustomWindow::present(Framebuffer& framebuffer) {
    HDC hdc = GetDC(reinterpret_cast<HWND>(platformWindow));
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = framebuffer.getWidth();
    bmi.bmiHeader.biHeight = -framebuffer.getHeight(); // Negative to flip the image vertically
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(hdc, 0, 0, framebuffer.getWidth(), framebuffer.getHeight(),
                  0, 0, framebuffer.getWidth(), framebuffer.getHeight(),
                  framebuffer.getBuffer().data(), &bmi, DIB_RGB_COLORS, SRCCOPY);

    ReleaseDC(reinterpret_cast<HWND>(platformWindow), hdc);
}
#elif defined(__unix__)

CustomWindow::CustomWindow(int width, int height, const std::string& title)
    : width(width), height(height), title(title), platformWindow(0) {
    // Constructor logic
    // Note: Do not call initialize() here
}

CustomWindow::~CustomWindow() {
    // Ensure that resources are cleaned up
    // cleanup();
}

void CustomWindow::initialize() {
    Display* display = XOpenDisplay(NULL);
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

void CustomWindow::cleanup() {
    if (platformWindow) {
        Display* display = XOpenDisplay(NULL);
        XDestroyWindow(display, platformWindow);
        XCloseDisplay(display);
        platformWindow = 0;
    }
}

void CustomWindow::mainLoop() {
    Display* display = XOpenDisplay(NULL);
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

void CustomWindow::present(Framebuffer& framebuffer) {
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Cannot open display\n";
        return;
    }

    int screen = DefaultScreen(display);

    XImage* image = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0,
                                 (char*)framebuffer.getBuffer().data(), width, height, 32, 0);

    if (!image) {
        std::cerr << "Failed to create XImage from framebuffer\n";
        XCloseDisplay(display);
        return;
    }

    GC gc = DefaultGC(display, screen);
    XPutImage(display, platformWindow, gc, image, 0, 0, 0, 0, width, height);

    image->data = NULL;  // Set data to NULL so that XDestroyImage will not free it
    XDestroyImage(image);

    XFlush(display);
    XCloseDisplay(display);
}

#endif

int CustomWindow::getWidth() const {
    return width;
}

int CustomWindow::getHeight() const {
    return height;
}
