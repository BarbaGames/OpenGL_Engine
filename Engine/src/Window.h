#pragma once
#include <glfw3.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();
    
    bool shouldClose() const;
    void swapBuffers() const;
    void makeContext() const;
    
    GLFWwindow* getWindow() const;
private:
    
    GLFWwindow* window;
};
