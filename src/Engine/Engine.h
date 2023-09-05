#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h> 

#define DLLExport __declspec(dllexport)

namespace MyEngine {
	// Circular declaration.
	class DLLExport Window;
	class DLLExport Renderer;

	class DLLExport Engine {
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