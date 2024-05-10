#pragma once
#include "Animation.h"
#include "TextBox.h"

const int8_t PIXELS_TO_MOVE = 3;
const int8_t NAMETAG_HEIGHT = 15;

struct CharacterState
{
    AnimationType animToPlay = AnimationType::DEFAULT;
    int8_t changeOfX = 0;
    int8_t changeOfY = 0;
};

class Character
{
  public:
    Character() = default;
    Character(const Rectangle &box, const Animation *animations, uint8_t size);
    Vector2 getPosition() const;
    const Rectangle &getRec() const;

    void Input();
    void Update();
    void Draw() const;
    void Move();
    void Play();

  private:
    CharacterState state;
    Vector2 position;
    Rectangle rec;
    Animation animations[5];
    uint8_t animationsCount = 5;
    TextBox nameTag;
};
