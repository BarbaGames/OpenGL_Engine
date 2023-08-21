#include <glfw3.h>
#include "Engine.h"

Engine::Engine() {
	glfwInit();
}

Engine::~Engine() {
	glfwTerminate();
}

void Engine::pollEvents() {
	glfwPollEvents();
}