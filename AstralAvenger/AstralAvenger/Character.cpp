#include "Character.h"
#include <iostream>

Character::Character(const Rectangle &box, const Animation *animations, uint8_t size)
    : nameTag("Na4alnik!",
              {box.x - NAMETAG_HEIGHT, box.y - NAMETAG_HEIGHT, box.width + 2 * NAMETAG_HEIGHT, NAMETAG_HEIGHT},
              GetFontDefault(), BLACK)
{
    this->rec = box;
    this->position = {box.x, box.y};

    for (int i = 0; i < size; i++)
    {
        this->animations[i] = animations[i];
    }

    animationsCount = size;
}

Vector2 Character::getPosition() const
{
    return position;
}

const Rectangle &Character::getRec() const
{
    return {position.x, position.y, rec.width, rec.height};
}

void Character::Input()
{
    state.animToPlay = AnimationType::DEFAULT;
    state.changeOfX = 0;
    state.changeOfY = 0;

    if (IsKeyDown(KEY_S))
    {
        state.animToPlay = AnimationType::MOVE_DOWN;
        state.changeOfY = PIXELS_TO_MOVE;
    }
    if (IsKeyDown(KEY_A))
    {
        state.animToPlay = AnimationType::MOVE_LEFT;
        state.changeOfX = -PIXELS_TO_MOVE;
    }
    if (IsKeyDown(KEY_D))
    {
        state.animToPlay = AnimationType::MOVE_RIGHT;
        state.changeOfX = PIXELS_TO_MOVE;
    }
    if (IsKeyDown(KEY_W))
    {
        state.animToPlay = AnimationType::MOVE_UP;
        state.changeOfY = -PIXELS_TO_MOVE;
    }
}

void Character::Update()
{
    Move();
    nameTag.setRectangle(
        {position.x - NAMETAG_HEIGHT, position.y - NAMETAG_HEIGHT, rec.width + 2 * NAMETAG_HEIGHT, NAMETAG_HEIGHT});
}

void Character::Draw() const
{
    animations[(int)state.animToPlay].play({position.x, position.y});
    nameTag.draw();
}

void Character::Move()
{
    int newPosX = position.x + state.changeOfX;
    int newPosY = position.y + state.changeOfY;

    if ((newPosX >= 0) && (newPosX <= GetScreenWidth() - rec.width) && (newPosY >= 0) &&
        (newPosY <= GetScreenHeight() - rec.height))
    {
        position.x = newPosX;
        position.y = newPosY;
    }
}

void Character::Play()
{
    Input();
    Update();
    Draw();
}
