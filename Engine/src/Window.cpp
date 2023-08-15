#include "Window.h"

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

void Window::swapBuffers() const
{
    glfwSwapBuffers(window);
}

void Window::makeContext() const
{
    glfwMakeContextCurrent(window);
}

GLFWwindow* Window::getWindow() const
{
    return window;
}
