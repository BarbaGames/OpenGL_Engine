#include "Window.h"

#include <iostream>

using namespace std;

namespace MyEngine {

    Window::Window(int width, int height, const char* title)
    {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    void Window::makeContext() const
    {
        glfwMakeContextCurrent(window);
    }

    GLFWwindow* Window::getWindow() const
    {
        return window;
    }

    int Window::getWindowWidth() {
        int windowWidth;
        glfwGetWindowSize(window, &windowWidth, nullptr);
        return windowWidth;
    }

    int Window::getWindowHeight() {
        int windowHeight;
        glfwGetWindowSize(window, nullptr, &windowHeight);
        return windowHeight;
    }

    float Window::getNormalizedX(int x) {
        int windowWidth = getWindowWidth();
        return (2.0f * x) / windowWidth - 1.0f;
    }

    float Window::getNormalizedY(int y) {
        int windowHeight = getWindowHeight();
        return (2.0f * y) / windowHeight - 1.0f;
    }
}
