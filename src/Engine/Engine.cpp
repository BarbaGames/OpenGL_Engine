#include <glfw3.h>
#include "Engine.h"

namespace MyEngine {

	Engine::Engine() {
		glfwInit();
	}

	Engine::~Engine() {
		glfwTerminate();
	}

	void Engine::pollEvents() {
		glfwPollEvents();
	}

}