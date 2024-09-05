#ifdef _WIN32  // This ensures that the code inside only compiles on Windows

#include <windows.h>  // Include Windows header for LRESULT, HWND, etc.
#include "window_winapi.hpp"
#include "../../core/framebuffer.hpp"

LRESULT CALLBACK WindowWinAPI::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WindowWinAPI* window = reinterpret_cast<WindowWinAPI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
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

WindowWinAPI::WindowWinAPI(int width, int height, const std::string& title)
    : CustomWindow(width, height, title), platformWindow(nullptr) {
    initialize();
}

WindowWinAPI::~WindowWinAPI() {
    cleanup();
}

void WindowWinAPI::initialize() {
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

void WindowWinAPI::cleanup() {
    if (platformWindow) {
        DestroyWindow(reinterpret_cast<HWND>(platformWindow));
        platformWindow = nullptr;
    }
}

void WindowWinAPI::mainLoop(std::function<void()> renderCallback) {
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // Run the rendering loop, process input, update the scene, etc.
            renderCallback();
        }
    }
}

int WindowWinAPI::getWidth() const {
    return width;
}

int WindowWinAPI::getHeight() const {
    return height;
}

void WindowWinAPI::present(Framebuffer& framebuffer) {
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

#endif  // End of _WIN32 guard
