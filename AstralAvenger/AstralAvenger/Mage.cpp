#include "Mage.h"

Mage::Mage(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap, const Animation *anim,
           Hero *target)
    : Enemy(hitBox, health, movementSpeed, tileMap, target)
{
    for (size_t i = 0; i < 6; i++)
    {
        this->animations[i] = anim[i];
    }
    this->damage = 1;
    this->movementSpeed = 2;
}

