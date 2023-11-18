#pragma once
#include "Rectangle.h"

using namespace MyEngine;

class CollisionManager
{
public:
    CollisionManager(Entity obstacles[]);
    ~CollisionManager();
    bool checkCollision(Entity* player);
    bool checkCollision(Transform transform);
    
private:
    Entity* obstacles[];
};
 