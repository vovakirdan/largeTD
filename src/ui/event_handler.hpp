#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

class EventHandler {
public:
    EventHandler();
    ~EventHandler();

    // Poll events (platform-specific)
    void pollEvents();

    // Handlers for different events
    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseClick(int button, int action);

private:
    // Store current state of inputs (e.g., pressed keys, mouse position)
    // Use a map or array to store key states and mouse position
};

#endif // EVENT_HANDLER_HPP
