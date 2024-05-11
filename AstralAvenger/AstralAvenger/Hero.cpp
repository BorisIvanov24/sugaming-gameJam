#include "Hero.h"

void Hero::play()
{
    input();
    update();
    draw();
}

void Hero::takeDamage(unsigned damage)
{
    health -= damage;
}

Hero::Hero(const Rectangle &hitBox, unsigned health, unsigned movementSpeed, const Animation *animations, const TileMap& tileMap)
    : Entity(hitBox, health, movementSpeed, tileMap), animations(animations)
{
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
    if ((IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) || (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) ||
        (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) || (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)))
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
    // healthbar
    // nametag
}

void Hero::move()
{
    int newPosX = hitBox.x + state.changeOfX;
    int newPosY = hitBox.y + state.changeOfY;
    
    if (newPosX < 0)
        newPosX = 0;

    if (newPosY < 0)
        newPosY = 0;

    unsigned newRowPos = getMatrixRowPosCustom((unsigned)newPosY);
    unsigned newColPos = getMatrixColPosCustom((unsigned)newPosX);

    if(tileMap.getValueAt(newRowPos, newColPos) == 0)
    {
        hitBox.x = newPosX;
        hitBox.y = newPosY;
    }
}
