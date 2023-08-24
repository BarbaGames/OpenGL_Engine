#pragma once
#include <glfw3.h>

namespace MyEngine {

    class Renderer
    {
    public:
        static void swapBuffers(GLFWwindow* window);
        static void clear();

        // Draw functions
        static void drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
    };

}
