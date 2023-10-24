#include <iostream>

#include "BaseGame.h"

// Namespace temporal
using namespace MyEngine;
using namespace std;

class Pong : public BaseGame {
private:
	Rectangle* rectangle;
	Rectangle* rectangle2;
	Sprite* sprite;
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
	rectangle = new Rectangle(/*Position*/ { 100, 100, 0 }, 
							  /*Size/Scale*/ {100, 100, 0}, 
							  /*Color*/ {255.0f, 128.0f, 0.0f});
	rectangle2 = new Rectangle(/*Position*/ { Window::getWindowWidth() * .5f, Window::getWindowHeight() * .7f, 0 }, 
							   /*Size/Scale*/ { 80, 80, 0 }, 
							   /*Color*/ { 170.0f, 0.0f, 255.0f });

	sprite = new Sprite(/*Position*/{ 500, 100, 0 },
						/*Size/Scale*/{ 50, 50, 0 },
						/*Color*/{ 255.0f, 255.0f, 255.0f});

	direction = 1;
}

Pong::~Pong() {

}

void Pong::init()
{
	unsigned int textureID = AssetLoader::loadImage("spaceship.png");
	sprite->setImage(textureID);
}

void Pong::update() {
	// When key 87 (W) is pressed, the rotation is to the other side. 
	rectangle->rotate({0, 0, 0, input->getKeyDown(87) ? 1.f : -1.f});
	rectangle2->move({ 2.0f * direction, 0, 0 });
	if (rectangle2->getTransform().position.x >= Window::getWindowWidth() * .8f || 
		rectangle2->getTransform().position.x <= Window::getWindowWidth() * .2f) {
		direction = -direction;
	}
	rectangle2->rotate({0, 0, 0, 1.5f * direction});
	sprite->rotate({0, 0, 0, 1.5f});
	
	cout << "Frame Time: " << ETime::getDeltaTime() << "\n";

	draw();
}

void Pong::uninit() {
	delete rectangle;
	delete rectangle2;
	delete sprite;
}

void Pong::draw() {
	Renderer::clear();

	rectangle->draw();
	rectangle2->draw();
	sprite->draw();
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}
