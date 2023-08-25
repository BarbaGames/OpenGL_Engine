#include <glew.h>
#include <glfw3.h>
#include "Engine.h"

#include <iostream>

using namespace std;

namespace MyEngine {

	Engine::Engine() {
		if (!glfwInit()) {
			cout << "(Error) Couldn't initialize GLFW context!\n";
		}
	}

	Engine::~Engine() {
		glfwTerminate();
	}

	void Engine::initGlew() {
		if (glewInit() != GLEW_OK) {
			cout << "(Error) Couldn't initialize GLEW context!\n";
		}
	}

	void Engine::pollEvents() {
		glfwPollEvents();
	}

}