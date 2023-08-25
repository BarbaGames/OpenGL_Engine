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


    void Renderer::drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y) {
        float positions[6] = {
            v1x, v1y,
            v2x, v2y,
            v3x, v3y
        };

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
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
