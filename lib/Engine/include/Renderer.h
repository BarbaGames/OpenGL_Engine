﻿#pragma once

#include "Engine.h"

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;

namespace MyEngine {

    class Renderer
    {
    private:
        static glm::mat4 projMatrix;
        static glm::mat4 viewMatrix;
        static glm::mat4 modelMatrix;

        static void setUpVertexAttributesShape();
        static void setUpVertexAttributesTexture();
        static unsigned int createVertexArrayObject();
        template <typename T, size_t N>
        static unsigned int createVertexBufferObject(const T(&vertexData)[N]);
        template <typename T, size_t N>
        static unsigned int createElementBufferObject(const T(&indices)[N]);

    public:
     
        static void swapBuffers(GLFWwindow* window);
        static void clear();
        // -- Draw functions --
        template <size_t N, size_t N2>
        static void drawShape(float(&vertexData)[N], unsigned int(&indices)[N2]);
        template <size_t N, size_t N2>
        static void drawTexture(float(&vertexData)[N], unsigned int(&indices)[N2], unsigned int textureID);
        static void drawRect(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y, float v4x, float v4y, float r, float g, float b);
        // Draws a triangle using modern OpenGL with normalized positions
        static void drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y, float r, float g, float b);
        // Draws a triangle using legacy OpenGL with normalized positions
        static void drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
        // Sets the dimentions of the projection matrix using a width and height
        static void set2DProjectionMatrix(float width, float height);
        // Sets the position of the view matrix
        static void setViewMatrix(float x, float y, float z);
        static void setViewMatrix(glm::mat4 newViewMatrix);
        // Sets the model matrix
        static void setModelMatrix(glm::mat4 newModelMatrix);

        static double getFrameTime();
    };

}
