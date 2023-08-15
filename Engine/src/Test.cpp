#include "Window.h"
#include <glfw3.h>

int main(void)
{
    // Initiating glfw context
    glfwInit();

    // Creating window
    Window window(640, 480, "Hello World");

    // Verifying window
    if (!window.getWindow())
    {
        glfwTerminate();
        return -1;
    }

    // Setting window to glfw context
    window.makeContext();

    /* Loop until the user closes the window */
    while (!window.shouldClose()) // Verifies if the window closes
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