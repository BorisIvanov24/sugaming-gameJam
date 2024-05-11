#include "Enemy.h"

Enemy::Enemy(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap)
    : Entity(hitBox, health, movementSpeed, tileMap)
{
}

void Enemy::play()
{
    input();
    update();
    draw();
    // damage
}

void Enemy::doDamage()
{
}

void Enemy::input()
{
    // state.animToPlay = AnimationType::DEFAULT;
    state.changeOfX = 0;
    state.changeOfY = 0;

    Vector2 myPos = getPositionWorld();
    Vector2 targetPos = target->getPositionWorld();

    if (targetPos.x < myPos.x) // horizontaly
    {
        state.animToPlay = AnimationType::MOVE_LEFT;
        state.changeOfX = -(int)movementSpeed;
    }
    else
    {
        state.animToPlay = AnimationType::MOVE_RIGHT;
        state.changeOfX = (int)movementSpeed;
    }

    if (targetPos.y < myPos.y) // verically
    {
        // state.animToPlay = AnimationType::MOVE_UP;
        state.changeOfX = -(int)movementSpeed;
    }
    else
    {
        // state.animToPlay = AnimationType::MOVE_DOWN;
        state.changeOfX = (int)movementSpeed;
    }

    if (state.changeOfX != 0 && state.changeOfY != 0)
    {
        state.changeOfX *= 0.75;
        state.changeOfY *= 0.75;
    }
}

void Enemy::update()
{
    move();
    // damage...
}

void Enemy::draw() const
{
    animations[(int)state.animToPlay].play({hitBox.x, hitBox.y});
}

void Enemy::move()
{
    int newPosX = hitBox.x + state.changeOfX;
    int newPosY = hitBox.y + state.changeOfY;

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
    }
}
