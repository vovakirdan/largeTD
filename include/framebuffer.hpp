#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <vector>
#include "Config.hpp"

class Framebuffer {
private:
    int width;
    int height;
    std::vector<uint32_t> buffer; // Assuming 32-bit color (RGBA)

public:
    Framebuffer(int width, int height);

    void clear(uint32_t color = Config::instance().getFramebufferDefaultColor()); // Clear with a specific color
    void setPixel(int x, int y, uint32_t color); // Set a pixel color
    const std::vector<uint32_t>& getBuffer() const; // Get the buffer data

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif // FRAMEBUFFER_HPP