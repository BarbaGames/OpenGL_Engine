#include <iostream>

#include "BaseGame.h"

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

}

void Pong::update() {

	draw();
}

void Pong::uninit() {

}

void Pong::draw() {
	Renderer::clear();

	Renderer::drawRect(0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.0f);
	Renderer::drawTriangle(window, 10, 80, 80, 10, 80, 80);
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}