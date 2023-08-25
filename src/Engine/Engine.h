#pragma once
#include <glew.h>
#include <glfw3.h>

namespace MyEngine {
	// Circular declaration.
	class Window;
	class Renderer;

	class Engine {
	public:
		Engine();
		~Engine();

		void initGlew();

		void pollEvents();
	};

}

// Circular declaration
#include "Window.h"
#include "Renderer.h"