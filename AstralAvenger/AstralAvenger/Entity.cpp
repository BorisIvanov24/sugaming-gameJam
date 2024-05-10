#include "Entity.h"

Entity::Entity(const Rectangle& hitBox, unsigned health, unsigned movementSpeed)
{
	this->hitBox = hitBox;
	//this->position = { hitBox.x, hitBox.y };
	this->health = health;
	this->movementSpeed = movementSpeed;
}

void Entity::setHealth(unsigned health)
{
	this->health = health;
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
	return { hitBox.x, hitBox.y };
}

unsigned Entity::getMatrixRowPos() const
{
	return hitBox.y / TILE_SIZE;
}

unsigned Entity::getMatrixColPos() const
{
	return hitBox.x / TILE_SIZE;
}
