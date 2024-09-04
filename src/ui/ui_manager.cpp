#include "ui_manager.hpp"
#include "ui_renderer.hpp"

UIManager::UIManager(UIRenderer* renderer)
        : renderer(renderer) {}

void UIManager::addComponent(UIComponent* component) {
    components.push_back(component);
}

void UIManager::renderUI() {
    for (auto& component : components) {
        component->draw(renderer);
    }
}

void UIManager::handleEvents(const EventHandler& event) {
    for (auto& component : components) {
        component->handleEvent(event);
    }
}

// UIButton class implementation
UIButton::UIButton(int x, int y, int width, int height, uint32_t color)
        : x(x), y(y), width(width), height(height), color(color) {}

void UIButton::draw(UIRenderer* renderer) {
    renderer->drawRectangle(x, y, width, height, color);
}

void UIButton::handleEvent(const EventHandler& event) {
    // TODO: Implement logic for button press, hover, etc.
}
