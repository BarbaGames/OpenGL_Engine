#include "BaseGame.h"

namespace MyEngine {
	// Private
	bool BaseGame::initBase() {
		if (!window->getWindow()) {
			delete engine;
			return -1;
		}

		window->makeContext(engine);
		window->setVsyncEnabled(true);

		Renderer::tempSetUpRedShader();

		init();
	}

	void BaseGame::updateBase() {
		while (!window->shouldClose()) // Verifies if the window closes
		{
			Renderer::clear();
			// Draw here ->

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
	}

	BaseGame::~BaseGame() {
		delete window;
		delete engine;
		uninitBase();
	}
}