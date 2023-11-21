#pragma once

#include "BaseGame.h"
#include "CollisionManager.h"

using namespace MyEngine;

class Parcial : public BaseGame {
private:
    CollisionManager* collisionManager;
    Sprite* background;
    Animation* sonic;
    Animation* sign;

    void init() override;
    void update() override;
    void uninit() override;
    void draw();
    void animationMovement(Animation* animation);
    void movement(Entity* player);
public:
    Parcial();
    ~Parcial() override;
};