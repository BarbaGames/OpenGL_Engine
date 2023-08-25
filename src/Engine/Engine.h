#pragma once

// Incluir Enigne tambien trae consigo las demas clases
#include "Window.h"
#include "Renderer.h"

namespace MyEngine {

	class Engine {
	public:
		Engine();
		~Engine();

		void initGlew();

		void pollEvents();
	};

}