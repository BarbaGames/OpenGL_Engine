#pragma once

#include "Engine.h"

#include <iostream>

using namespace std;

namespace MyEngine {

    class Renderer
    {
    private:
        static unsigned int compileShader(unsigned int type, string& source);
        static int createShader(string& vertexShader, string& fragmentShader);
        static void setUpVertexAttributes(unsigned int& buffer);
        template <typename T, size_t N>
        static unsigned int createVertexBuffer(const T(&vertexData)[N]);
    public:
        struct ShaderProgramSource
        {
            string VertexSource;
            string FragmentSource;
        };
        
        // (temp) Creates a shader program that draws everything red
        static void tempSetUpRedShader();
        static void swapBuffers(GLFWwindow* window);
        static void clear();

        // Reads a file containing shaders and returns them
        static ShaderProgramSource parseShader(const string& filepath);
        // -- Draw functions --
        // Draws a triangle using modern OpenGL with normalized positions
        static void drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
        // Draws a triangle using modern OpenGL with window pixel positions
        static void drawTriangle(Window* window, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y);
        // Draws a triangle using legacy OpenGL with normalized positions
        static void drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
        // Draws a triangle using legacy OpenGL with window pixel positions
        static void drawTriangleLegacy(Window* window, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y);
    };

}
