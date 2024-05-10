#pragma once
#include "raylib.h"
#include "Constants.h"

class Entity
{
public:
	Entity() = default;
	Entity(const Rectangle& hitBox, unsigned health, unsigned movementSpeed);
	
	void setHealth(unsigned health);
	void setMovementSpeed(unsigned movementSpeed);

	unsigned getHealth() const;
	unsigned getMovementSpeed() const;
	Vector2 getPositionWorld() const;

	unsigned getMatrixRowPos() const;
	unsigned getMatrixColPos() const;

private:

	Rectangle hitBox = {0, 0, 32, 64};
	//Vector2 position = { 0, 0 };
	unsigned health = 100;
	unsigned movementSpeed = 2; //how many pixels to move per frame

};

