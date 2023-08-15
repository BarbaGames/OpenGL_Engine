#include <glfw3.h>

#include "Window.h"
#include "Renderer.h"

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
        Renderer::clear();

        /* Swap front and back buffers */
        Renderer::swapBuffers(window.getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}