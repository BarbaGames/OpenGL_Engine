#include "Game.h"
#include <iostream>
#include <string>

#include "Dictionary.h"


// Namespace temporal

using namespace std;

Game::Game()
{
    floorCollision = new Rectangle(/*Position*/ {Window::getWindowWidth() * .5f, Window::getWindowHeight() * .95f, 0},
                                                /*Size/Scale*/ {static_cast<float>(Window::getWindowWidth()), 80, 0},
                                                /*Color*/ {170.0f, 0.0f, 255.0f});

    signboard = new Animation({Window::getWindowWidth() * .1f, Window::getWindowHeight() * .1f, 0}, {75, 75, 0},
                              {255.0f, 255.0f, 255.0f});
    watermark = new Animation({Window::getWindowWidth() * .8f, Window::getWindowHeight() * .9f, 0}, {255, 43, 0},
                              {255.0f, 255.0f, 255.0f});
    player = new Animation({Window::getWindowWidth() * .1f, Window::getWindowHeight() * .7f, 0}, {100, 100, 0},
                           {255.0f, 255.0f, 255.0f});
    background = new Sprite({Window::getWindowWidth() * .5f, Window::getWindowHeight() * .5f, 0}, {
                                static_cast<float>(Window::getWindowWidth()),
                                static_cast<float>(Window::getWindowHeight()), 0
                            }, {255.0f, 255.0f, 255.0f});

    std::vector<Entity*> obstacles = {static_cast<Entity*>(signboard), static_cast<Entity*>(floorCollision)};

    collisionManager = new CollisionManager(obstacles);
}

Game::~Game()
{
}

void Game::init()
{
    unsigned int spritesheetId = AssetLoader::loadImage("pikachu-spritesheet.png", "Pikachu");
    unsigned int backgroundID = AssetLoader::loadImage("background.png", "Background");
    background->setImage(backgroundID);

    float frameWidth = 1.0f / (847.f / 38.f);
    float frameHeight = 1.0f / (396.f / 47.f);

    for (int i = 1; i < 3; i++)
    {
        player->addFrame("idle", spritesheetId, frameWidth * i + frameWidth * 3.58f, 0, frameWidth, frameHeight);
    }

    frameWidth = 1.0f / 17.28f;
    frameHeight = 1.0f / 9.42f;

    for (int i = 0; i < 4; ++i)
    {
        player->addFrame("walking", spritesheetId, 10.79f * frameWidth + frameWidth * i, frameHeight * 1.45f,
                         frameWidth,
                         frameHeight);
    }

    frameWidth = 1.f / 4.48f;
    frameHeight = 1.f / 2.69f;

    signboard->addFrame("idle", spritesheetId, 1.85f * frameWidth, frameHeight * 1.67f, frameWidth,
                        frameHeight);

    frameWidth = 1.f / 3.32f;
    frameHeight = 1.f / 9.2f;
    watermark->addFrame("idle", spritesheetId, frameWidth * 2.3f, frameHeight * 5.9f, frameWidth, frameHeight);
    player->setDurationInSecs(2.f);
    player->setCurrentAnimation("idle");

    signboard->setDurationInSecs(2.f);
    signboard->setCurrentAnimation("idle");
    watermark->setDurationInSecs(1.f);
    watermark->setCurrentAnimation("idle");
}

void Game::update()
{
    movement(player);
    animationMovement();
    player->update();
    signboard->update();
    string title = "Engine Test (FPS: " + to_string(ETime::getFPS()) + ")";

    window->setTitle(title.c_str());

    draw();
}

void Game::uninit()
{
    delete floorCollision;
    delete player;
    delete background;
    delete signboard;
}

void Game::draw()
{
    Renderer::clear();

    background->draw();
    player->draw();
    signboard->draw();
    watermark->draw();
}

void Game::animationMovement()
{
    if (input->isKeyDown())
    {
        player->setCurrentAnimation("walking");
    }
    else
    {
        player->setCurrentAnimation("idle");
    }
}

void Game::movement(Animation* player)
{
    Transform transform2 = player->getTransform();
    transform2.position.y += 1.f;
    if (!collisionManager->checkCollision(transform2))
    {
        player->move({0.f, 1.f, 0});
    }
    if (!input->isKeyDown()) return;
    Transform transform = player->getTransform();

    if (input->getKeyDown(Key_D))
    {
        // D
        transform.position.x += 2.0f;

        if (!collisionManager->checkCollision(transform))
        {
            player->move({2.f, 0.f, 0.f});
        }
    }

    if (input->getKeyDown(Key_W))
    {
        // W
        transform.position.y -= 2.0f;
        if (!collisionManager->checkCollision(transform))
        {
            player->move({0.f, -2.f, 0.f});
        }
    }

    if (input->getKeyDown(Key_S))
    {
        // S
        transform.position.y += 2.0f;
        if (!collisionManager->checkCollision(transform))
        {
            player->move({0.f, 2.f, 0.f});
        }
    }

    if (input->getKeyDown(Key_A))
    {
        // A

        transform.position.x -= 2.0f;
        if (!collisionManager->checkCollision(transform))
        {
            player->move({-2.f, 0.f, 0.f});
        }
    }
}
