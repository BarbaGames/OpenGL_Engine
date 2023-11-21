#pragma once
#include "BaseGame.h"
#include "CollisionManager.h"

using namespace MyEngine;

class Game : public BaseGame
{
private:
    CollisionManager* collisionManager;
    Rectangle* floorCollision;
    Animation* signboard;
    Animation* player;
    Sprite* background;
    int direction;

    void init() override;
    void update() override;
    void uninit() override;
    void draw();
    void animationMovement(Animation* animation, string indexDown, string indexRight, string indexUp, string indexLeft); // Hardcodeadisimo, pero por ahora sirve.
    void movement(Entity* player);

public:
    Game();
    ~Game() override;
};
