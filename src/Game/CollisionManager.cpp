#include "CollisionManager.h"

CollisionManager::CollisionManager(const std::vector<Entity*>& obstacles) : obstacles{obstacles}
{
}

CollisionManager::~CollisionManager()
{
    for (Entity* obstacle : obstacles) {
        delete obstacle;
    }

    obstacles.clear();
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
