#pragma once
#include "Constants.h"
#include "raylib.h"

class Entity
{
  public:
    Entity() = default;
    Entity(const Rectangle &hitBox, unsigned health, unsigned movementSpeed);

    void setHealth(unsigned health);
    void setMovementSpeed(unsigned movementSpeed);

    unsigned getHealth() const;
    unsigned getMovementSpeed() const;
    Vector2 getPositionWorld() const;

    unsigned getMatrixRowPos() const;
    unsigned getMatrixColPos() const;

    const Rectangle &getHitBox() const;

  protected:
    Rectangle hitBox = {0, 0, 32, 64};
    // Vector2 position = { 0, 0 };
    unsigned health = 100;
    unsigned movementSpeed = 2; // how many pixels to move per frame
};
