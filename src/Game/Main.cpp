#include "Engine/Engine.h"

// Namespace temporal
using namespace MyEngine;

int main() {
	// Initiating glfw context (As pointer so we can uninit it manually to test)
	Engine* engine = new Engine();
	// Initiating window
	Window window(640, 480, "Hello World");

	// We verify that the window inits correctly
	if (!window.getWindow()) {
		delete engine;
		return -1;
	}

	// Setting window to glfw context
	window.makeContext();

	// Loop until the user closes the window
	while (!window.shouldClose()) // Verifies if the window closes
	{
		// Render here
		Renderer::clear();

		Renderer::drawTriangleLegacy(-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f);

		// Swap front and back buffers
		Renderer::swapBuffers(window.getWindow());

		// Poll for and process events
		engine->pollEvents();
	}

	// Uninit
	delete engine; // We uninit engine
	return 0;
}