#pragma once

#include "Engine.h"

namespace MyEngine {

    class Renderer
    {
    public:
        static void swapBuffers(GLFWwindow* window);
        static void clear();

        // Draw functions

        // Draws a triangle using modern OpenGL with normalized positions.
        static void drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
        // Draws a triangle using legacy OpenGL with normalized positions.
        static void drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
        // Draws a triangle using legacy OpenGL with window pixel positions.
        static void drawTriangleLegacy(Window* window, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y);
    };

}
