#pragma once
#include "BaseGame.h"
#include "CollisionManager.h"

using namespace MyEngine;

class Game : public BaseGame
{
private:
    CollisionManager* collisionManager;
    Rectangle* rectangle;
    Rectangle* rectangle2;
    Sprite* sprite;
    Sprite* sprite2;
    Animation* animCoin;
    Animation* animBat;
    int direction;

    void init() override;
    void update() override;
    void uninit() override;
    void draw();
    void movement(Entity* player);

public:
    Game();
    ~Game() override;
};
