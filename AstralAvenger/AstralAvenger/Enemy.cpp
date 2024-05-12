#include "Enemy.h"

bool Enemy::hitboxesOn = false;

Enemy::Enemy(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap, Hero *target)
    : Entity(hitBox, health, movementSpeed, tileMap)
{
    this->target = target;
}

void Enemy::play()
{
    input();
    update();
    draw();
    if (CheckCollisionRecs(getHitBox(), target->getHitBox()))
    {
        target->takeDamage(damage);
    }
}

void Enemy::input()
{

    if (hurtPlaying)
    {
        return;
    }

    // state.animToPlay = AnimationType::DEFAULT;
    state.changeOfX = 0;
    state.changeOfY = 0;

    Vector2 myPos = getPositionWorld();
    Vector2 targetPos = target->getPositionWorld();

    if ((int)targetPos.x < (int)myPos.x) // horizontaly
    {
        state.changeOfX = -(int)movementSpeed;
    }
    else if ((int)targetPos.x > (int)myPos.x)
    {
        state.changeOfX = (int)movementSpeed;
    }

    if ((int)targetPos.y < (int)myPos.y) // verically
    {
        state.changeOfY = -(int)movementSpeed;
    }
    else if ((int)targetPos.y > (int)myPos.y)
    {
        state.changeOfY = (int)movementSpeed;
    }

    if (state.changeOfX != 0 && state.changeOfY != 0)
    {
        state.changeOfX *= 0.75;
        state.changeOfY *= 0.75;
    }

    if (state.changeOfX < 0)
    {
        state.animToPlay = AnimationType::MOVE_LEFT;
    }
    else if (state.changeOfX > 0)
    {
        state.animToPlay = AnimationType::MOVE_RIGHT;
    }
    else
    {
        if (state.changeOfY > 0)
        {
            state.animToPlay = AnimationType::MOVE_DOWN;
        }
        else if (state.changeOfY < 0)
        {
            state.animToPlay = AnimationType::MOVE_UP;
        }
        else
        {
            state.animToPlay = AnimationType::DEFAULT;
        }
    }
}
void Enemy::takeDamage(unsigned damage)
{
    health -= damage;

    hurtPlaying = true;
    state.animToPlay = AnimationType::HURT;
}

void Enemy::setHitBoxes()
{
    hitboxesOn = !hitboxesOn;
}

void Enemy::update()
{
    move();
    // damage...
}

void Enemy::draw()
{
    if (hurtPlaying)
    {
        hurtPlaying = animations[(int)state.animToPlay].playRun({hitBox.x, hitBox.y});
        
        if (hitboxesOn)
        DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, ORANGE);
        return;
    }
    animations[(int)state.animToPlay].play({hitBox.x, hitBox.y});
    if (hitboxesOn)
    DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, ORANGE);
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
