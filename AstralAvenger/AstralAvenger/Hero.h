#pragma once
#include "Animation.h"
#include "Constants.h"
#include "Entity.h"
#include "TileMap.h"
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
    Hero(const Rectangle &hitBox, int health, unsigned movementSpeed, const Animation *animations,
         const TileMap &tileMap);

    void play();
    unsigned getCooldownWhip() const;
    const Rectangle &getWhipRec() const;

    unsigned getDamage() const;
    void setDamage(unsigned damage);
    void playWhip() const;
    void setWhipPlaying();

  private:
    void input();
    void update();
    void draw();
    void move();

    Animation animations[6];
    HeroState state;
    TextBox nameTag;
    Rectangle whipRec;
    unsigned cooldownWhip = 2;
    unsigned damage = 50;
    bool whipPlaying = false;

    // atacks/wepons //healthbar
};
