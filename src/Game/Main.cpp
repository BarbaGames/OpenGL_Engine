#include <iostream>
#include <string>

#include "BaseGame.h"

// Namespace temporal
using namespace MyEngine;
using namespace std;

class Pong : public BaseGame {
private:
	Rectangle* rectangle;
	Rectangle* rectangle2;
	Sprite* sprite;
	Sprite* sprite2;
	Animation* animCoin;
	Animation* animBat;
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
						/*Size/Scale*/ { 50, 50, 0 },
						/*Color*/{ 255.0f, 255.0f, 255.0f});

	sprite2 = new Sprite(/*Position*/ { Window::getWindowWidth() * .5f, Window::getWindowHeight() * .7f, 0 },
						 /*Size/Scale*/ { 35, 35, 0 },
						 /*Color*/{ 255.0f, 255.0f, 255.0f });

	animCoin = new Animation(/*Position*/{ Window::getWindowWidth() * .3f, Window::getWindowHeight() * .7f, 0 },
						 /*Size/Scale*/{ 50, 50, 0 },
						 /*Color*/{ 255.0f, 255.0f, 255.0f });

	animBat = new Animation(/*Position*/{ Window::getWindowWidth() * .5f, Window::getWindowHeight() * .3f, 0 },
							/*Size/Scale*/{ 75, 75, 0 },
							/*Color*/{ 255.0f, 255.0f, 255.0f });

	direction = 1;
}

Pong::~Pong() {

}

void Pong::init()
{
	unsigned int textureID = AssetLoader::loadImage("spaceship.png", "Spaceship");
	sprite->setImage(textureID);
	unsigned int textureID2 = AssetLoader::loadImage("sus.png", "Amogus");
	sprite2->setImage(textureID2);
	unsigned int coinTX = AssetLoader::loadImage("coinSS.png", "CoinSS");
	animCoin->setSpriteSheet(coinTX, 8, 1, 1.0);
	unsigned int batTX = AssetLoader::loadImage("batSS.png", "BatSS");
	// Esto esta todo hardcodeado, pero es un ejemplo de como manualmente setear los frames.
	float frameWidth = 1.0f / 4;
	float frameHeight = 1.0f / 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j > 0) {
				animBat->addFrame(batTX, frameWidth * j, frameHeight * i, frameWidth, frameHeight);
			}
		}
	}
	animBat->setDurationInSecs(1.5);
	// 
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
	sprite2->rotate({ 0, 0, 0, -0.1f });
	if (direction > 0) {
		sprite2->setMirrorX(false);
	}
	else {
		sprite2->setMirrorX(true);
	}
	animCoin->update();
	animBat->update();

	string title = "Engine Test (FPS: " + to_string(ETime::getFPS()) + ")";

	window->setTitle(title.c_str());

	draw();
}

void Pong::uninit() {
	delete rectangle;
	delete rectangle2;
	delete sprite;
	delete sprite2;
	delete animCoin;
	delete animBat;
}

void Pong::draw() {
	Renderer::clear();

	rectangle->draw();
	rectangle2->draw();
	sprite->draw();
	sprite2->draw();
	animCoin->draw();
	animBat->draw();
}

int main() {
	Pong myGame;
	myGame.runGame();
	return 0;
}
