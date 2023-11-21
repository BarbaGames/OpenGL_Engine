#include "Parcial.h"

#include "Dictionary.h"

Parcial::Parcial() {
	background = new Sprite(/*Position*/{ Window::getWindowWidth() * .5f, Window::getWindowHeight() * .5f, 0 },
		/*Size/Scale*/{ 1000, 1000, 0 },
		/*Color*/{ 255.0f, 255.0f, 255.0f });

	sonic = new Animation(/*Position*/{ Window::getWindowWidth() * .5f, Window::getWindowHeight() * .5f, 0 },
		/*Size/Scale*/{ 50, 60, 0 },
		/*Color*/{ 255.0f, 255.0f, 255.0f });

	sign = new Animation(/*Position*/{ Window::getWindowWidth() * .5f, Window::getWindowHeight() * .3f, 0 },
		/*Size/Scale*/{ 50, 50, 0 },
		/*Color*/{ 255.0f, 255.0f, 255.0f });

	std::vector<Entity*> obstacles = { static_cast<Entity*>(sign) };

	collisionManager = new CollisionManager(obstacles);
}

Parcial::~Parcial() {

}

void Parcial::init() {
	unsigned int bg = AssetLoader::loadImage("background.png", "sonic_background");
	unsigned int sS = AssetLoader::loadImage("Sonic_Mania_Sprite_Sheet.png", "sonic_spritesheet");

	background->setImage(bg);

	//
	float frameWidth = 0.034;
	float frameHeight = 0.08;
	for (int i = 1; i < 5; i++) {
		sonic->addFrame("idle", sS, frameWidth * i, frameHeight * 2.0f, frameWidth, frameHeight);
	}
	frameWidth = 0.038;
	frameHeight = 0.08;
	for (int i = 9; i < 21; i++) {
		sonic->addFrame("run", sS, frameWidth * i, frameHeight * 3.2f, frameWidth, frameHeight);
	}
	sonic->setDurationInSecs(1.0);
	sonic->setCurrentAnimation("idle");
	//

	//
	frameWidth = 0.04;
	frameHeight = 0.08;
	for (int i = 5; i < 10; i++) {
		sign->addFrame(sS, frameWidth * i, frameHeight * 8.6f, frameWidth, frameHeight);
	}
	sign->setDurationInSecs(2.0);
	//
}

void Parcial::update() {
	movement(sonic);
	animationMovement(sonic);

	sonic->update();
	sign->update();

	draw();
}

void Parcial::uninit() {
	delete background;
	delete sonic;
	delete sign;
}

void Parcial::draw() {
	Renderer::clear();
	background->draw();

	sonic->draw();
	sign->draw();
}

void Parcial::animationMovement(Animation* animation) {
	if (input->getKeyDown(Key_A) || input->getKeyDown(Key_D) || input->getKeyDown(Key_W) || input->getKeyDown(Key_S)) {
		animation->setCurrentAnimation("run");
	}
	else if (input->getKeyUp(Key_A) || input->getKeyUp(Key_D) || input->getKeyDown(Key_W) || input->getKeyDown(Key_S)) {
		animation->setCurrentAnimation("idle");
	}
}

void Parcial::movement(Entity* player) {
	if (!input->isKeyDown()) return;
	Transform transform = player->getTransform();

	if (input->getKeyDown(Key_D)) {// D
		transform.position.x += 2.0f;
		if (!collisionManager->checkCollision(transform)) {
			player->move({ 2.f, 0.f,0.f });
		}
	}

	if (input->getKeyDown(Key_W)) { // W
		transform.position.y -= 2.0f;
		if (!collisionManager->checkCollision(transform))
		{
			player->move({ 0.f, -2.f,0.f });
		}
	}

	if (input->getKeyDown(Key_S)) { // S
		transform.position.y += 2.0f;
		if (!collisionManager->checkCollision(transform))
		{
			player->move({ 0.f, 2.f,0.f });
		}
	}

	if (input->getKeyDown(Key_A)) { // A
		transform.position.x -= 2.0f;
		if (!collisionManager->checkCollision(transform))
		{
			player->move({ -2.f, 0.f,0.f });
		}
	}
}