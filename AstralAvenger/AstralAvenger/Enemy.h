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
    Enemy(const Rectangle &hitBox, int health, unsigned movementSpeed, const TileMap &tileMap, Hero *target);

    void play();
    virtual ~Enemy() = default;
    void takeDamage(unsigned damage) override;
    void setHitBoxes();
    static bool hitboxesOn;

  protected:
    void input();
    void update();
    void draw();
    void move();

    Animation animations[6];
    Hero *target = nullptr;
    unsigned damage = 0;
    unsigned attackSpeed = 0;
    EnemyState state;
    bool hurtPlaying = false;
    
};
