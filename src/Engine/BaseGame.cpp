#include "BaseGame.h"

#include "Shader.h"

namespace MyEngine {
	BaseGame::BaseGame() {
		engine = new Engine();
		window = new Window(640, 480, "Base Game");
		input = new Input(window->getWindow());
	}

	BaseGame::~BaseGame() {
		uninitBase();
		delete input;
		delete window;
		delete engine;
	}

	// Private
	bool BaseGame::initBase() {
		if (!window->getWindow()) {
			delete engine;
			return false;
		}

		window->makeContext(engine);
		window->setVsyncEnabled(true);

		Shader::loadBasicShaders();

		init();
		updateBase();
		return true;
	}

	void BaseGame::updateBase() {
		while (!window->shouldClose()) // Verifies if the window closes
		{
			ETime::updateFrameTime();
			update();

			// Swap front and back buffers
			Renderer::swapBuffers(window->getWindow());

			// Poll for and process events
			engine->pollEvents();
		}
	}

	void BaseGame::uninitBase() {
		uninit();

		Shader::unloadBasicShaders();
		AssetLoader::unloadAllImages();
	}

	// Public

	void BaseGame::runGame() {
		initBase();
	}
}