#pragma once

#include "Engine.h"

namespace MyEngine {

    class Window
    {
    private:
        static int windowWidth;
        static int windowHeight;

        GLFWwindow* window;

    public:
        Window(int width, int height, const char* title);
        ~Window();

        // Returns if the window was closed
        bool shouldClose() const;
        // Adds glfw context to the window
        void makeContext(Engine* engine) const;

        // Changes the title of the window
        void setTitle(const char* title);

        // Enables or disables vsync (This will limit the fps to your monitor's maximum saving you gpu resources.)
        void setVsyncEnabled(bool set);

        // Returns the active instance of glfw window
        GLFWwindow* getWindow() const;

        // Returns the pixel width of the window
        static int getWindowWidth();

        // Returns the pixel height of the window
        static int getWindowHeight();
    };

}