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

// Removed this declaration
// class UIButton : public UIComponent {
//     // Implement a basic button
// };

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
