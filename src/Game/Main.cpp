#include <iostream>

#include "BaseGame.h"

// Ejercicio 3
using namespace MyEngine;
using namespace std;

struct Vector3 {
	float x;
	float y;
	float z;
};

class Parcial : public BaseGame {
private:
    void init() override;
    void update() override;
    void uninit() override;
    void draw();
    glm::mat4 trans;
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;

public:
	Parcial();
	~Parcial() override;
};

Parcial::Parcial() {
    trans = glm::mat4(1.0f);
	v1 = { 0.0f, 100.0f, 0.0f };
	v2 = { 50.0f, 0.0f, 0.0f };
	v3 = { 100.0f, 100.0f, 0.0f };
}

Parcial::~Parcial() {

}

void Parcial::init()
{

}

void Parcial::update() {

	draw();
}

void Parcial::uninit() {

}

void Parcial::draw() {
	Renderer::clear();

	trans = glm::translate(glm::mat4(1.0f), glm::vec3(-.8f + (Renderer::getFrameTime() * .25f),
													  -.7f + (Renderer::getFrameTime() * .25f),
													  0.0f));
	trans = glm::rotate(trans, glm::radians(((float)Renderer::getFrameTime() * 50.0f)), glm::vec3(0.0f, 0.0f, 1.0f));

	Renderer::setModelMatrix(trans);

	Renderer::drawTriangle( (window->getWindowWidth() * .4f) + v1.x,
							(window->getWindowHeight() * .4f) + v1.y,
							(window->getWindowWidth() * .4f) + v2.x,
							(window->getWindowHeight() * .4f) + v2.y,
							(window->getWindowWidth() * .4f) + v3.x,
							(window->getWindowHeight() * .4f) + v3.y,
							1.0f, 0.2f, 0.2f);
	trans = glm::mat4(1.0f);
}

int main() {
	Parcial myGame;
	myGame.runGame();
	return 0;
}
