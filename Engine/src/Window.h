#pragma once
#include <glfw3.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();
    
    // Returns if the window was closed
    bool shouldClose() const;
    // Swaps front buffer with back buffer
    void swapBuffers() const;
    // Adds context to the window (Sets it to glfw by default)
    void makeContext() const;
    
    // Returns the active instance of glfw window
    GLFWwindow* getWindow() const;
private:
    
    GLFWwindow* window;
};
