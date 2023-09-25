#include "Window.h"

#include <iostream>

using namespace std;

namespace MyEngine {

    Window::Window(int width, int height, const char* title)
    {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        Renderer::set2DProjectionMatrix(static_cast<float>(width), static_cast<float>(height));
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

    void Window::makeContext(Engine* engine) const
    {
        glfwMakeContextCurrent(window);
        // Initializing GLEW
        engine->initGlew();
    }

    void Window::setVsyncEnabled(bool set) {
        glfwSwapInterval(set);
    }

    GLFWwindow* Window::getWindow() const
    {
        return window;
    }

    int Window::getWindowWidth() const 
    {
        int windowWidth;
        glfwGetWindowSize(window, &windowWidth, nullptr);
        return windowWidth;
    }

    int Window::getWindowHeight() const 
    {
        int windowHeight;
        glfwGetWindowSize(window, nullptr, &windowHeight);
        return windowHeight;
    }
}
