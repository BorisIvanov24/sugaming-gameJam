#pragma once
#include "Animation.h"
#include "Constants.h"
#include "Entity.h"
#include "raylib.h"

struct HeroState
{
    AnimationType animToPlay = AnimationType::DEFAULT;
    int8_t changeOfX = 0;
    int8_t changeOfY = 0;
};

class Hero : public Entity
{
  public:
    Hero() = default;
    Hero(const Rectangle &hitBox, unsigned health, unsigned movementSpeed, const Animation *animations);

    void play();
    void takeDamage(unsigned damage);

  private:
    void input();
    void update();
    void draw() const;
    void move();

    const Animation *animations;
    HeroState state;
    TextBox nameTag;
    // atacks/wepons //healthbar
};
