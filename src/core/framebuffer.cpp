#include "framebuffer.hpp"

Framebuffer::Framebuffer(int width, int height) : width(width), height(height), buffer(width * height, Config::instance().getFramebufferDefaultColor()) {}

void Framebuffer::clear(uint32_t color) {
    std::fill(buffer.begin(), buffer.end(), color);
}

void Framebuffer::setPixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[y * width + x] = color;
    }
}

const std::vector<uint32_t>& Framebuffer::getBuffer() const {
    return buffer;
}