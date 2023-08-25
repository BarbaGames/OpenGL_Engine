#include "Renderer.h"

namespace MyEngine {

    void Renderer::swapBuffers(GLFWwindow* window)
    {
        glfwSwapBuffers(window);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void Renderer::drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y) {
        glBegin(GL_TRIANGLES);
            glVertex2f(v1x, v1y);
            glVertex2f(v2x, v2y);
            glVertex2f(v3x, v3y);
        glEnd();
    }

    void Renderer::drawTriangleLegacy(Window* window, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y) {
        glBegin(GL_TRIANGLES);
            glVertex2f(window->getNormalizedX(v1x), window->getNormalizedX(v1y));
            glVertex2f(window->getNormalizedX(v2x), window->getNormalizedX(v2y));
            glVertex2f(window->getNormalizedX(v3x), window->getNormalizedX(v3y));
        glEnd();
    }
}
