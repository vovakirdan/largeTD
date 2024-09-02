#include "ui_renderer.hpp"

UIRenderer::UIRenderer(Framebuffer* framebuffer)
    : framebuffer(framebuffer) {}

void UIRenderer::drawRectangle(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int px = x + j;
            int py = y + i;
            if (px >= 0 && px < framebuffer->getWidth() && py >= 0 && py < framebuffer->getHeight()) {
                framebuffer->setPixel(px, py, color);
            }
        }
    }
}

void UIRenderer::drawLine(int x1, int y1, int x2, int y2, uint32_t color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        framebuffer->setPixel(x1, y1, color);

        if (x1 == x2 && y1 == y2) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void UIRenderer::drawText(int x, int y, const std::string& text, uint32_t color) {
    // Placeholder implementation
    // For simplicity, let's just represent characters as small squares
    for (char c : text) {
        drawRectangle(x, y, 8, 8, color); // Each character is an 8x8 block
        x += 10; // Move to the next character position
    }
}
