#ifndef WINDOW_WINAPI_HPP
#define WINDOW_WINAPI_HPP

#include "window.hpp"
#include <windows.h>

class WindowWinAPI : public Window {
public:
    WindowWinAPI(int width, int height, const std::string& title);
    ~WindowWinAPI() override;

    void initialize() override;
    void cleanup() override;
    void mainLoop() override;
    void present(Framebuffer& framebuffer) override;

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // WINDOW_WINAPI_HPP
