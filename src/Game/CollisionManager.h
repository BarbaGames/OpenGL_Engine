#pragma once
#include "Rectangle.h"

using namespace MyEngine;

class CollisionManager
{
public:
    CollisionManager(const std::vector<Entity*>& obstacles);
    ~CollisionManager();
    bool checkCollision(Entity* player);
    bool checkCollision(Transform transform);
    
private:
    std::vector<Entity*> obstacles;
};
 