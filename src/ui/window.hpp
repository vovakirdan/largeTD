#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

class Window {
public:
    // Constructor to create a window of a specific size
    Window(int width, int height, const std::string& title);
    ~Window();

    // Main loop to run the window
    void mainLoop();

    // Getters
    int getWidth() const;
    int getHeight() const;

private:
    int width, height;
    std::string title;

    // Platform-specific window handle (like HWND on Windows, Window on X11)
    void* windowHandle;

    // Initialize the window (platform-specific)
    void initialize();

    // Cleanup resources (platform-specific)
    void cleanup();
};

#endif // WINDOW_HPP
