#include "Input.h"

Input::Input(GLFWwindow* window) : window(window) {
}

bool Input::getKeyDown(int key) {
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

bool Input::getKeyUp(int key) {
    return (glfwGetKey(window, key) == GLFW_RELEASE);
}

bool Input::getMouseButtonDown(int button) {
    return (glfwGetMouseButton(window, button) == GLFW_PRESS);
}

bool Input::getMouseButtonUp(int button) {
    return (glfwGetMouseButton(window, button) == GLFW_RELEASE);
}

float Input::getMouseX() const
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return xpos;
}

float Input::getMouseY() const
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return ypos;
}
