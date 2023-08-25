#pragma once
#include <glfw3.h>

namespace MyEngine {

    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        // Returns if the window was closed
        bool shouldClose() const;
        // Adds context to the window (Sets it to glfw by default)
        void makeContext() const;

        // Returns the active instance of glfw window
        GLFWwindow* getWindow() const;

        // Returns the pixel width of the window
        int getWindowWidth();

        // Returns the pixel height of the window
        int getWindowHeight();

        // Receives a pixel position on screen and returns the normalized position for OpenGl.
        float getNormalizedX(int x);
        float getNormalizedY(int y);

    private:

        GLFWwindow* window;
    };

}