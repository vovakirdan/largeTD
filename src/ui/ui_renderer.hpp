#ifndef UI_RENDERER_HPP
#define UI_RENDERER_HPP

#include "../core/framebuffer.hpp"
#include <iostream>

class UIRenderer {
public:
    UIRenderer(Framebuffer* framebuffer);

    // Basic UI drawing functions
    void drawRectangle(int x, int y, int width, int height, uint32_t color);
    void drawLine(int x1, int y1, int x2, int y2, uint32_t color);
    void drawText(int x, int y, const std::string& text, uint32_t color);

private:
    Framebuffer* framebuffer;
    // Need a font renderer or bitmap font for drawing text
};

#endif // UI_RENDERER_HPP
