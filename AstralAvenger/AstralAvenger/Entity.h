#pragma once
#include "Constants.h"
#include "TileMap.h"
#include "raylib.h"

unsigned getMatrixRowPosCustom(unsigned x);
unsigned getMatrixColPosCustom(unsigned y);

class Entity
{
  public:
    Entity() = default;
    Entity(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap);

    void setHealth(unsigned health);
    void setMovementSpeed(unsigned movementSpeed);

    unsigned getHealth() const;
    unsigned getMovementSpeed() const;
    Vector2 getPositionWorld() const;

    unsigned getMatrixRowPos() const;
    unsigned getMatrixColPos() const;

    bool isAlive() const;

    const Rectangle &getHitBox() const;

  protected:
    Rectangle hitBox = {0, 0, 32, 64};
    // Vector2 position = { 0, 0 };
    int health = 100;
    unsigned movementSpeed = 2; // how many pixels to move per frame

    const TileMap &tileMap;
};
