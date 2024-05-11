#include "Hero.h"
#include <iostream>

void Hero::play()
{
    input();
    update();
    draw();

    //  std::cout << health << std::endl;
}

unsigned Hero::getCooldownWhip() const
{
    return cooldownWhip;
}

const Rectangle &Hero::getWhipRec() const
{
    return whipRec;
}

unsigned Hero::getDamage() const
{
    return damage;
}

void Hero::setDamage(unsigned damage)
{
    this->damage = damage;
}

Hero::Hero(const Rectangle &hitBox, int health, unsigned movementSpeed, const Animation *animations,
           const TileMap &tileMap)
    : Entity(hitBox, health, movementSpeed, tileMap)
{
    for (size_t i = 0; i < 5; i++) // copy animations
    {
        this->animations[i] = animations[i];
    }

    whipRec = {hitBox.x - 64, hitBox.y - 64, 160, 64};
    cooldownWhip = 2;
}

void Hero::input()
{

    state.animToPlay = AnimationType::DEFAULT;
    state.changeOfX = 0;
    state.changeOfY = 0;

    if (IsKeyDown(KEY_S))
    {
        state.animToPlay = AnimationType::MOVE_DOWN;
        state.changeOfY = movementSpeed;
    }
    if (IsKeyDown(KEY_A))
    {
        state.animToPlay = AnimationType::MOVE_LEFT;
        state.changeOfX = -(int)movementSpeed;
    }
    if (IsKeyDown(KEY_D))
    {
        state.animToPlay = AnimationType::MOVE_RIGHT;
        state.changeOfX = movementSpeed;
    }
    if (IsKeyDown(KEY_W))
    {
        state.animToPlay = AnimationType::MOVE_UP;
        state.changeOfY = -(int)movementSpeed;
    }
    // diagonaly
    if (state.changeOfX != 0 && state.changeOfY != 0)
    {
        state.changeOfX *= 0.75;
        state.changeOfY *= 0.75;
    }
}

void Hero::update()
{
    move();
    // nametag
    // healthbar
}

void Hero::draw() const
{
    animations[(int)state.animToPlay].play({hitBox.x, hitBox.y});
    DrawRectangleLines(whipRec.x, whipRec.y, whipRec.width, whipRec.height, BLACK);
    DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLACK);
    // nametag
}

void Hero::move()
{
    int newPosX = hitBox.x + state.changeOfX;
    int newPosY = hitBox.y + state.changeOfY;

    int newWhipPosX = whipRec.x + state.changeOfX;
    int newWhipPosY = whipRec.y + state.changeOfY;

    if (newPosX < 0)
        newPosX = 0;

    if (newPosY < 0)
        newPosY = 0;

    unsigned newRowPos = getMatrixRowPosCustom((unsigned)newPosY);
    unsigned newColPos = getMatrixColPosCustom((unsigned)newPosX);

    if (tileMap.getValueAt(newRowPos, newColPos) == 0)
    {
        hitBox.x = newPosX;
        hitBox.y = newPosY;
        whipRec.x = newWhipPosX;
        whipRec.y = newWhipPosY;
    }
}
