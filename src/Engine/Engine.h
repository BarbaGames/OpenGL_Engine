#pragma once

// Incluir Enigne tambien trae consigo las demas clases
#include "Window.h"
#include "Renderer.h"

class Engine {
public:
	Engine();
	~Engine();

	void pollEvents();
};
