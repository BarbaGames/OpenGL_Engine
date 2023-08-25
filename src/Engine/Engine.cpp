#include "Engine.h"

#include <iostream>

using namespace std;

namespace MyEngine {

	Engine::Engine() {
		if (!glfwInit()) {
			cout << "(Error) Couldn't initialize GLFW context!\n";
		}
		else {
			cout << "Initialized GLFW successfully!\n";
		}
	}

	Engine::~Engine() {
		glfwTerminate();
	}

	void Engine::initGlew() {
		if (glewInit() != GLEW_OK) {
			cout << "(Error) Couldn't initialize GLEW!\n";
		}
		else {
			cout << "Initialized GLEW successfully!\n";
		}
	}

	void Engine::pollEvents() {
		glfwPollEvents();
	}

}