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

	Renderer::drawRect(200, 200, 200, 100, 100, 100, 100, 200, 0.5f, 0.0f, 1.0f);
	Renderer::drawTriangle(10, 80, 80, 10, 80, 80, 1.0f, 0.5f, 0.0f, (float)Renderer::getFrameTime() * 50.0f);
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}