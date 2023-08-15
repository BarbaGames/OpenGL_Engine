#pragma once
#include <glfw3.h>

class Renderer
{
public:
    static void swapBuffers(GLFWwindow* window);
    static void clear();
};
