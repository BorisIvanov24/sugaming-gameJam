#pragma once
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "raylib.h"

struct EnemyState
{
    AnimationType animToPlay = AnimationType::DEFAULT;
    int8_t changeOfX = 0;
    int8_t changeOfY = 0;
};

class Enemy : public Entity
{

  public:
    Enemy() = default;
    Enemy(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap);

    void play();
    void doDamage();
    virtual ~Enemy() = default;
    virtual void levelUp() = 0;

  protected:
    void input();
    void update();
    void draw() const;
    void move();

    const Animation* animations;
    const Hero* target;
    unsigned damage = 0;
    unsigned attackSpeed = 0;
    EnemyState state;
};
