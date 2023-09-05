#include "Engine/Engine.h"
#include <iostream>

#include "Engine/BaseGame.h"

// Namespace temporal
using namespace MyEngine;
using namespace std;


class Pong : public BaseGame {
private:
	void init() override;
	void update() override;
	void uninit() override;
	void draw();
public:
	Pong();
	~Pong() override;
};

Pong::Pong() {

}

Pong::~Pong() {

}

void Pong::init() {
	cout << "hi\n";
}

void Pong::update() {
	cout << ".";
	draw();
}

void Pong::uninit() {

}

void Pong::draw() {
	Renderer::clear();

	Renderer::drawRect(0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f);
	//Renderer::drawTriangle(&window, 10, 80, 80, 10, 80, 80);
}

int main() {
	//Pong* myGame = new Pong();
	Pong myGame();
	//delete myGame;
	return 0;
}

/*
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
	window.makeContext(engine);
	window.setVsyncEnabled(true);

	Renderer::tempSetUpRedShader(); // This is a temp function.

	// Loop until the user closes the window
	while (!window.shouldClose()) // Verifies if the window closes
	{
		Renderer::clear();
		// Draw here ->

		Renderer::drawRect(0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f);
		Renderer::drawTriangle(&window, 10, 80, 80, 10, 80, 80);

		// Swap front and back buffers
		Renderer::swapBuffers(window.getWindow());

		// Poll for and process events
		engine->pollEvents();
	}

	// Uninit
	delete engine; // We uninit engine
	return 0;
}
*/