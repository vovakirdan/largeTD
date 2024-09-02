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

// Example implementation of a button
class UIButton : public UIComponent {
public:
    UIButton(int x, int y, int width, int height, uint32_t color)
            : x(x), y(y), width(width), height(height), color(color) {}

    void draw(UIRenderer* renderer) override {
        renderer->drawRectangle(x, y, width, height, color);
    }

    void handleEvent(const EventHandler& event) override {
        //todo Implement logic for button press, hover, etc.
    }

private:
    int x, y, width, height;
    uint32_t color;
};
