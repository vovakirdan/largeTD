#include "window.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#endif

#ifdef _WIN32
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
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
#endif

Window::Window(int width, int height, const std::string& title)
    : width(width), height(height), title(title), platformWindow(0) {
    initialize();
}

Window::~Window() {
    cleanup();
}

#ifdef _WIN32
void Window::initialize() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "WindowClass";

    RegisterClass(&wc);

    platformWindow = CreateWindowEx(
        0,
        "WindowClass",
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

void Window::cleanup() {
    if (platformWindow) {
        DestroyWindow(reinterpret_cast<HWND>(platformWindow));
        platformWindow = nullptr;
    }
}

void Window::mainLoop() {
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

void Window::present(Framebuffer& framebuffer) {
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

void Window::initialize() {
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

void Window::cleanup() {
    if (platformWindow) {
        Display* display = XOpenDisplay(NULL);
        XDestroyWindow(display, platformWindow);
        XCloseDisplay(display);
        platformWindow = 0;
    }
}

void Window::mainLoop() {
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

void Window::present(Framebuffer& framebuffer) {
    // TODO: Implement framebuffer drawing for X11 (or use shared memory)
}

#endif

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}
