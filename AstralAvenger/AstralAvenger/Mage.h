#pragma once
#include "Enemy.h"
class Mage : public Enemy
{
  public:
    Mage() = default;
    Mage(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap, const Animation *anim,
         Hero *target);
};
