#include "Window.h"

#include <iostream>

using namespace std;

namespace MyEngine {

    int Window::windowWidth = 0;
    int Window::windowHeight = 0;

    Window::Window(int width, int height, const char* title)
    {
        windowWidth = width;
        windowHeight = height;
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

    int Window::getWindowWidth() 
    {
        return windowWidth;
    }

    int Window::getWindowHeight() 
    {
        return windowHeight;
    }
}
