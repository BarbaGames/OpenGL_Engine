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
    glm::mat4 trans;
    float x;
    float y;

public:
	Pong();
	~Pong() override;
};

Pong::Pong() {

}

Pong::~Pong() {

}

void Pong::init()
{
    //scale and rotation test
    trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    Renderer::setModelMatrix(trans);

    trans = glm::mat4(1.0f);
    
}

void Pong::update() {

	draw();
}

void Pong::uninit() {

}

void Pong::draw() {
	Renderer::clear();

    Renderer::setModelMatrix(glm::mat4(1.f)); // this line is so that the Rect doesn't get rotated

    Renderer::drawRect(200, 200, 200, 100, 100, 100, 100, 200, 0.5f, 0.0f, 1.0f);

    trans = glm::rotate(trans, glm::radians(1.f), glm::vec3(0.0f, 0.0f, 1.0f));

    Renderer::setModelMatrix(trans);

    Renderer::drawTriangle(10, 80, 80, 10, 80, 80, 1.0f, 0.5f, 0.0f);
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}
