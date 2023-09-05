#include "BaseGame.h"
#include <iostream>

using namespace std;

namespace MyEngine {
	// Private
	bool BaseGame::initBase() {
		if (!window->getWindow()) {
			delete engine;
			return false;
		}

		window->makeContext(engine);
		window->setVsyncEnabled(true);

		Renderer::tempSetUpRedShader();

		init();
	}

	void BaseGame::updateBase() {
		while (!window->shouldClose()) // Verifies if the window closes
		{
			update();

			// Swap front and back buffers
			Renderer::swapBuffers(window->getWindow());

			// Poll for and process events
			engine->pollEvents();
		}
	}

	void BaseGame::uninitBase() {

		uninit();
	}

	// Public
	BaseGame::BaseGame() {
		engine = new Engine();
		window = new Window(640, 480, "Base Game");
		initBase();
		updateBase();
	}

	BaseGame::~BaseGame() {
		uninitBase();
		delete window;
		delete engine;
	}
}