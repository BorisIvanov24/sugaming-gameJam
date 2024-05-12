#include "Entity.h"

Entity::Entity(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap) : tileMap(tileMap)
{
    this->hitBox = hitBox;
    // this->position = { hitBox.x, hitBox.y };
    this->health = health;
    this->movementSpeed = movementSpeed;
}

void Entity::setHealth(unsigned health)
{
    this->health = health;
}

void Entity::takeDamage(unsigned damage)
{
    health -= damage;
}

void Entity::heal()
{
    if(health<1180)
    health += 100;
}

void Entity::setMovementSpeed(unsigned movementSpeed)
{
    this->movementSpeed = movementSpeed;
}

unsigned Entity::getHealth() const
{
    return health;
}

unsigned Entity::getMovementSpeed() const
{
    return movementSpeed;
}

Vector2 Entity::getPositionWorld() const
{
    return {hitBox.x, hitBox.y};
}

unsigned getMatrixRowPosCustom(unsigned x)
{
    return x / TILE_SIZE;
}

unsigned getMatrixColPosCustom(unsigned y)
{
    return y / TILE_SIZE;
}

unsigned Entity::getMatrixRowPos() const
{
    return hitBox.y / TILE_SIZE;
}

unsigned Entity::getMatrixColPos() const
{
    return hitBox.x / TILE_SIZE;
}

bool Entity::isAlive() const
{
    return health > 0;
}

const Rectangle &Entity::getHitBox() const
{
    return hitBox;
}
