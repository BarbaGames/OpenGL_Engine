#include "Game.h"
#include <iostream>
#include <string>

#include "Dictionary.h"


// Namespace temporal

using namespace std;

Game::Game() {
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
	std::vector<Entity*> obstacles = { static_cast<Entity*>(rectangle2), static_cast<Entity*>(sprite), static_cast<Entity*>(sprite2),
		static_cast<Entity*>(animCoin) };
	
	collisionManager = new CollisionManager(obstacles);
}

Game::~Game() {

}

void Game::init() {
	unsigned int textureID = AssetLoader::loadImage("spaceship.png", "Spaceship");
	sprite->setImage(textureID);
	unsigned int textureID2 = AssetLoader::loadImage("sus.png", "Amogus");
	sprite2->setImage(textureID2);
	unsigned int coinTX = AssetLoader::loadImage("coinSS.png", "CoinSS");
	animCoin->setSpriteSheet(coinTX, 8, 1, 1.0);
	unsigned int batTX = AssetLoader::loadImage("batSS.png", "BatSS");

	// Esto esta todo hardcodeado, pero es un ejemplo de como manualmente setear los frames y añadir multiples indices a una animacion.
	float frameWidth = 1.0f / 4;
	float frameHeight = 1.0f / 4;
	for (int i = 1; i < 4; i++) { // Empiezo en 1 por que quiero saltearme el primer slot del spritesheet.
		animBat->addFrame("down", batTX, frameWidth * i, 0, frameWidth, frameHeight); // Le pongo nombre como indice, en este caso este indice es en el que el murcielago va para abajo.
	}
	for (int i = 1; i < 4; i++) {
		animBat->addFrame("right", batTX, frameWidth * i, frameHeight * 1, frameWidth, frameHeight); // Multiplico la altura por la fila.
	}
	for (int i = 1; i < 4; i++) {
		animBat->addFrame("up", batTX, frameWidth * i, frameHeight * 2, frameWidth, frameHeight);
	}
	for (int i = 1; i < 4; i++) {
		animBat->addFrame("left", batTX, frameWidth * i, frameHeight * 3, frameWidth, frameHeight);
	}
	animBat->setDurationInSecs(.5);
	animBat->setCurrentAnimation("down");
	//

}

void Game::update() {
	movement(animBat);
	animationMovement(animBat, "down", "right", "up", "left");

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

void Game::uninit() {
	delete rectangle2;
	delete sprite;
	delete sprite2;
	delete animCoin;
	delete animBat;
}

void Game::draw() {
	Renderer::clear();
	
	rectangle2->draw();
	sprite->draw();
	sprite2->draw();
	animCoin->draw();
	animBat->draw();
}

void Game::animationMovement(Animation* animation, string indexDown, string indexRight, string indexUp, string indexLeft) {
	if (!input->isKeyDown()) return;

	if (input->getKeyDown(Key_W)) { // W
		if (animation->getCurrentAnimation() == indexUp) return;
		animation->setCurrentAnimation(indexUp);
	}

	if (input->getKeyDown(Key_A)) { // A
		if (animation->getCurrentAnimation() == indexLeft) return;
		animation->setCurrentAnimation(indexLeft);
	}

	if (input->getKeyDown(Key_D)) {// D
		if (animation->getCurrentAnimation() == indexRight) return;
		animation->setCurrentAnimation(indexRight);
	}

	if (input->getKeyDown(Key_S)) { // S
		if (animation->getCurrentAnimation() == indexDown) return;
		animation->setCurrentAnimation(indexDown);
	}
}

void Game::movement(Entity* player) {
	if(!input->isKeyDown()) return;
	Transform transform = player->getTransform();
	
	if(input->getKeyDown(Key_D)) {// D
		transform.position.x += 2.0f;
		if(!collisionManager->checkCollision(transform)) {
			player->move({2.f, 0.f,0.f});
		}
	}
	
	if(input->getKeyDown(Key_W)) { // W
		transform.position.y -= 2.0f;
		if(!collisionManager->checkCollision(transform))
		{
			player->move({0.f, -2.f,0.f});
		}
	}

	if(input->getKeyDown(Key_S)) { // S
		transform.position.y += 2.0f;
		if(!collisionManager->checkCollision(transform))
		{
			player->move({0.f, 2.f,0.f});
		}
	}
	
	if(input->getKeyDown(Key_A)) { // A
		transform.position.x -= 2.0f;
		if(!collisionManager->checkCollision(transform))
		{
			player->move({-2.f, 0.f,0.f});
		}
	}
}
