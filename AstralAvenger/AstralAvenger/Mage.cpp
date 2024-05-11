#include "Mage.h"

Mage::Mage(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap, const Animation *anim,
           const Hero *target)
    : Enemy(hitBox, health, movementSpeed, tileMap)
{
    animations = anim;
    this->target = target;
    this->damage = 5;
    this->movementSpeed = 2;
}
