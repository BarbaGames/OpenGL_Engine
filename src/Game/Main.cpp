#include <iostream>
#include "BaseGame.h"
#include <ext/matrix_transform.hpp>
#include "glfw3.h"

// Namespace temporal
using namespace MyEngine;
using namespace std;

class Pong : public BaseGame {
private:
	void init() override;
	void update() override;
	void uninit() override;
	void draw();
	
	glm::mat4 transform;
public:
	Pong();
	~Pong() override;
};

Pong::Pong() {
	transform = glm::mat4(1.0f);
}

Pong::~Pong() {

}

void Pong::init() {

}
void Pong::update() {
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)Renderer::getFrameTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	Renderer::setMVPMatrix(transform);
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