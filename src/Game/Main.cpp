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
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	float triangleVertex[6];
	float rotationAngle = 0;

public:
	Pong();
	~Pong() override;
};

Pong::Pong() {

}

Pong::~Pong() {

}

void Pong::init(){

	trans = glm::mat4(1.0f);
	Renderer::setModelMatrix(trans);

	triangleVertex[0] = 10.0f;
	triangleVertex[1] = 400.0f;
	triangleVertex[2] = 100.0f;
	triangleVertex[3] = 400.0;
	triangleVertex[4] = 55.0f;
	triangleVertex[5] = 300.0f;
};

void Pong::update() {
	
	rotationAngle = 10.f;

	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.7f, .6f, 0.0f));

	rotation = glm::rotate(rotation, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	
	trans = glm::translate(trans, glm::vec3(0.03f, 0.03f, 0.0f));
	model = trans * rotation;
	
	Renderer::setModelMatrix(model);
	
	draw();
}

void Pong::uninit() {

}

void Pong::draw() {

	Renderer::clear();
	
	Renderer::drawTriangle(triangleVertex[0], triangleVertex[1], triangleVertex[2], triangleVertex[3], triangleVertex[4], triangleVertex[5], 1.0f, 0.0f, 0.0f);
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}
