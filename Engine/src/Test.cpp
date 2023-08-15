#include "Window.h"
#include <glfw3.h>

int main(void)
{
    glfwInit();

    Window window(640, 480, "Hello World");

    if (!window.getWindow())
    {
        glfwTerminate();
        return -1;
    }

    window.makeContext();

    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}