﻿#include "Renderer.h"

void Renderer::swapBuffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}