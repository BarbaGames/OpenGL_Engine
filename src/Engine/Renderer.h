#pragma once
#include <glfw3.h>

namespace MyEngine {

    class Renderer
    {
    public:
        static void swapBuffers(GLFWwindow* window);
        static void clear();
    };

}
