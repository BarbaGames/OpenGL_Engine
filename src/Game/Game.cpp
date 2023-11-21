#include "Game.h"
#include <iostream>
#include <string>

#include "Dictionary.h"


// Namespace temporal

using namespace std;

Game::Game() {
	floorCollision = new Rectangle(/*Position*/ { Window::getWindowWidth() * .5f, Window::getWindowHeight() * .95f, 0 }, 
							   /*Size/Scale*/ { static_cast<float>(Window::getWindowWidth()), 80, 0 }, 
							   /*Color*/ { 170.0f, 0.0f, 255.0f });
	
	signboard = new Animation({Window::getWindowWidth() * .5f, Window::getWindowHeight() * .7f, 0}, { 75, 75, 0 },{ 255.0f, 255.0f, 255.0f } );

	player = new Animation({Window::getWindowWidth() * .1f, Window::getWindowHeight() * .7f, 0}, { 100, 100, 0 } ,{ 255.0f, 255.0f, 255.0f });
	background = new Sprite({Window::getWindowWidth() * .5f, Window::getWindowHeight() * .5f, 0}, { static_cast<float>(Window::getWindowWidth()), static_cast<float>(Window::getWindowHeight()), 0 } ,{ 255.0f, 255.0f, 255.0f });

	std::vector<Entity*> obstacles = { static_cast<Entity*>(signboard), static_cast<Entity*>(floorCollision) };
	
	collisionManager = new CollisionManager(obstacles);
}

Game::~Game() {

}

void Game::init() {
	unsigned int atlasID = AssetLoader::loadImage("Sonic_Atlas.png", "Sonic");
	unsigned int backgroundID = AssetLoader::loadImage("background.png", "Background");
	background->setImage(backgroundID);


	float frameWidth = 1.0f / 22.8f;
	float frameHeight = 1.0f / 11.07f;
	std::cout << 121/ frameHeight ;
	for (int i = 7; i < 18; i++) { 
		player->addFrame("walking", atlasID, frameWidth * i + frameWidth * 0.36f, frameHeight * 2.88f	, frameWidth, frameHeight); 
	}
	frameWidth = 1.0f / 17;
	frameHeight = 1.0f / 10;	
	for (int i = 3; i < 8; i++) { 
		signboard->addFrame("idle", atlasID, frameWidth * i + frameWidth*0.74f, frameHeight * 7, frameWidth, frameHeight); 
	}
	
	player->setDurationInSecs(2.f);
	player->setCurrentAnimation("walking");
	
	signboard->setDurationInSecs(2.f);
	signboard->setCurrentAnimation("idle");
	
}

void Game::update() {
	movement(player);
	
	player->update();
	signboard->update();
	string title = "Engine Test (FPS: " + to_string(ETime::getFPS()) + ")";

	window->setTitle(title.c_str());

	draw();
}

void Game::uninit() {
	delete floorCollision;
	delete player;
	delete background;
	delete signboard;
}

void Game::draw() {
	Renderer::clear();
	
	background->draw();
	player->draw();
	signboard->draw();
}

void Game::animationMovement(Animation* animation, string indexDown, string indexRight, string indexUp, string indexLeft) {
	if (!input->isKeyDown()) return;

	if (input->getKeyDown(Key_W)) { // W
		animation->setCurrentAnimation(indexUp);
	}

	if (input->getKeyDown(Key_A)) { // A
		animation->setCurrentAnimation(indexLeft);
	}

	if (input->getKeyDown(Key_D)) {// D
		animation->setCurrentAnimation(indexRight);
	}

	if (input->getKeyDown(Key_S)) { // S
		animation->setCurrentAnimation(indexDown);
	}
}

void Game::movement(Entity* player) {
	Transform transform2 = player->getTransform();
	transform2.position.y += 1.f;
	if(!collisionManager->checkCollision(transform2))
	{
		player->move({0.f, 1.f, 0});
	}
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
