#pragma once

#include "Engine.h"

class DLLExport Input {
public:
    // Constructor
    Input(GLFWwindow* window);

    // Key input functions
    bool getKeyDown(int key);
    bool getKeyUp(int key);

    // Mouse input functions
    bool getMouseButtonDown(int button);
    bool getMouseButtonUp(int button);
    
    float getMouseX() const;
    float getMouseY() const;
private:
    GLFWwindow* window;
    glm::dvec2 mousePosition;
    glm::dvec2 prevMousePosition;
    bool keys[GLFW_KEY_LAST + 1] = { false };
    bool mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1] = { false };
    
};
