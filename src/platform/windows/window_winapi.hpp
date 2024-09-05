#ifndef WINDOW_WINAPI_HPP
#define WINDOW_WINAPI_HPP

#include "../../ui/window.hpp"
#include <functional>
#ifdef _WIN32
#include <windows.h>

class WindowWinAPI : public CustomWindow {
public:
    WindowWinAPI(int width, int height, const std::string& title);
    ~WindowWinAPI() override;

    void initialize() override;
    void cleanup() override;
    void mainLoop(std::function<void()> renderCallback) override;
    int getWidth() const;
    int getHeight() const;
    void present(Framebuffer& framebuffer) override;

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND platformWindow;
};

#endif
#endif // WINDOW_WINAPI_HPP
