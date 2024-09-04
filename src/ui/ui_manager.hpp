#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <vector>
#include "ui_renderer.hpp"
#include "event_handler.hpp"

class UIComponent {
public:
    virtual void draw(UIRenderer* renderer) = 0;
    virtual void handleEvent(const EventHandler& event) = 0;
};

// UIButton class declaration
class UIButton : public UIComponent {
public:
    UIButton(int x, int y, int width, int height, uint32_t color);

    void draw(UIRenderer* renderer) override;
    void handleEvent(const EventHandler& event) override;

private:
    int x, y, width, height;
    uint32_t color;
};

class UIManager {
public:
    UIManager(UIRenderer* renderer);

    void addComponent(UIComponent* component);
    void renderUI();
    void handleEvents(const EventHandler& event);

private:
    std::vector<UIComponent*> components;
    UIRenderer* renderer;
};

#endif // UI_MANAGER_HPP
