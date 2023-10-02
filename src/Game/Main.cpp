#include <iostream>

#include "BaseGame.h"

// Namespace temporal
using namespace MyEngine;
using namespace std;

class Pong : public BaseGame {
private:
	Rectangle* rectangle;
	Rectangle* rectangle2;
    void init() override;
    void update() override;
    void uninit() override;
    void draw();

	int direction;

public:
	Pong();
	~Pong() override;
};

Pong::Pong() {
	rectangle = new Rectangle(/*Position*/ {-.5, .5, 0}, /*Size/Scale*/ {100, 100, 0}, /*Color*/ {255.0f, 128.0f, 0.0f});
	rectangle2 = new Rectangle(/*Position*/{ .5, -.5, 0 }, /*Size/Scale*/{ 80, 80, 0 }, /*Color*/{ 170.0f, 0.0f, 255.0f });
	direction = 1;
}

Pong::~Pong() {

}

void Pong::init()
{

}

void Pong::update() {
	rectangle->rotate({0, 0, 0, 1});
	rectangle2->move({ .02f * direction, 0, 0 });
	if (rectangle2->getTransform().position.x >= .7 || rectangle2->getTransform().position.x <= -.7) {
		direction = -direction;
	}
	rectangle2->rotate({0, 0, 0, -5.0f * direction });
	draw();
}

void Pong::uninit() {
	delete rectangle;
	delete rectangle2;
}

void Pong::draw() {
	Renderer::clear();

	rectangle->draw();
	rectangle2->draw();
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}
