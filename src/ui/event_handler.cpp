#include "event_handler.hpp"
#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#else
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#endif

EventHandler::EventHandler() {}
EventHandler::~EventHandler() {}

void EventHandler::pollEvents() {
#ifdef _WIN32
    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#elif defined(__unix__)
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        return; // Handle error
    }

    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);
        switch (event.type) {
            case KeyPress:
                onKeyDown(XLookupKeysym(&event.xkey, 0));
                break;
            case KeyRelease:
                onKeyUp(XLookupKeysym(&event.xkey, 0));
                break;
            case MotionNotify:
                onMouseMove(event.xmotion.x, event.xmotion.y);
                break;
            case ButtonPress:
                onMouseClick(event.xbutton.button, ButtonPress);
                break;
            case ButtonRelease:
                onMouseClick(event.xbutton.button, ButtonRelease);
                break;
            default:
                break;
        }
    }
    XCloseDisplay(display);
#endif
}

void EventHandler::onKeyDown(int key) {
    // Handle key down events here
}

void EventHandler::onKeyUp(int key) {
    // Handle key up events here
}

void EventHandler::onMouseMove(int x, int y) {
    // Handle mouse move events here
}

void EventHandler::onMouseClick(int button, int action) {
    // Handle mouse click events here
}

#ifdef _WIN32
LRESULT CALLBACK EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    EventHandler* handler = reinterpret_cast<EventHandler*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (!handler) return DefWindowProc(hwnd, uMsg, wParam, lParam);

    switch (uMsg) {
        case WM_KEYDOWN:
            handler->onKeyDown(static_cast<int>(wParam));
            break;
        case WM_KEYUP:
            handler->onKeyUp(static_cast<int>(wParam));
            break;
        case WM_MOUSEMOVE:
            handler->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        case WM_LBUTTONDOWN:
            handler->onMouseClick(VK_LBUTTON, WM_LBUTTONDOWN);
            break;
        case WM_LBUTTONUP:
            handler->onMouseClick(VK_LBUTTON, WM_LBUTTONUP);
            break;
        case WM_RBUTTONDOWN:
            handler->onMouseClick(VK_RBUTTON, WM_RBUTTONDOWN);
            break;
        case WM_RBUTTONUP:
            handler->onMouseClick(VK_RBUTTON, WM_RBUTTONUP);
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
#endif
