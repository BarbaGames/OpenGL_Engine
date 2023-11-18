#include "CollisionManager.h"

CollisionManager::CollisionManager(Entity obstacles[]) : obstacles{obstacles}
{
}

CollisionManager::~CollisionManager()
{
    delete obstacles;
}

bool CollisionManager::checkCollision(Entity* player)
{
    for (Entity* obstacle : obstacles)
    {
        if(obstacle->isColliding(player->getTransform()))
        {
            return true;
        }
    }
    return false;
}

bool CollisionManager::checkCollision(Transform transform)
{
    for (Entity* obstacle : obstacles)
    {
        if(obstacle->isColliding(transform))
        {
            return true;
        }
    }
    return false;
}
