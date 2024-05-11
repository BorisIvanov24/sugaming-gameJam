#include "Constants.h"
#include "Enemy.h"
#include "Hero.h"
#include "Item.h"
#include "Mage.h"
#include "TileMap.h"
#include "raylib.h"
#include <iostream>
#include <vector>

int coinsCount = 0;

Animation *loadHeroAnims(unsigned count)
{
    Animation *res = new Animation[count];
    res[(int)AnimationType::DEFAULT].loadFromFolder("Assets/Hero/walkRight/walkRight_", 1);
    res[(int)AnimationType::MOVE_UP].loadFromFolder("Assets/Hero/walkUp/walkUp_", 8);
    res[(int)AnimationType::MOVE_LEFT].loadFromFolder("Assets/Hero/walkLeft/walkLeft_", 8);
    res[(int)AnimationType::MOVE_RIGHT].loadFromFolder("Assets/Hero/walkRight/walkRight_", 8);
    res[(int)AnimationType::MOVE_DOWN].loadFromFolder("Assets/Hero/walkRight/walkRight_", 8);
    return res;
}

Animation *loadMageAnims(unsigned count)
{
    Animation *res = new Animation[count];
    res[(int)AnimationType::DEFAULT].loadFromFolder("Assets/Mage/MageWalkRight/MageWalkRight_", 1);
    res[(int)AnimationType::MOVE_UP].loadFromFolder("Assets/Mage/MageWalkRight/MageWalkRight_", 8);
    res[(int)AnimationType::MOVE_LEFT].loadFromFolder("Assets/Mage/MageWalkLeft/MageWalkLeft_", 8);
    res[(int)AnimationType::MOVE_RIGHT].loadFromFolder("Assets/Mage/MageWalkRight/MageWalkRight_", 8);
    res[(int)AnimationType::MOVE_DOWN].loadFromFolder("Assets/Mage/MageWalkLeft/MageWalkLeft_", 8);
    res[(int)AnimationType::HURT].loadFromFolder("Assets/MageHurt/MageHurt_", 7);
    return res;
}

Animation *loadItemAnims()
{
    Animation *res = new Animation;
    res->loadFromFolder("Assets/Coin/coin_", 4);

    return res;
}

void spawnEnemies(std::vector<Enemy *> &enemies, const TileMap &tilemap, const Animation *anim, Hero &hero)
{
    // 3
    Rectangle random = {(float)(100 + rand() % 3900), (float)(100 + rand() % 3900), 32, 32};
    Enemy *newEn = new Mage(random, 100, 3, tilemap, anim, &hero);
    enemies.push_back(newEn);
}

void playEnemies(std::vector<Enemy *> &enemies)
{
    for (auto i : enemies)
    {
        i->play();
    }
    // std::cout << "enemies count" << enemies.size() << std::endl;
}

void playItems(std::vector<Item *> &items, const Hero &hero)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (CheckCollisionRecs(hero.getHitBox(), items[i]->hitBox()))
        {
            coinsCount++;
            delete items[i];
            items.erase(items.begin() + i);
            i--;
        }
        else
        {
            items[i]->Draw();
        }
    }
}

void whipAtack(std::vector<Enemy *> &enemies, const Hero &hero, std::vector<Item *> &items, const Animation &itemAnim)
{

    for (int i = 0; i < enemies.size(); i++)
    {
        if (CheckCollisionRecs(hero.getWhipRec(), enemies[i]->getHitBox()))
        {
            enemies[i]->takeDamage(hero.getDamage());
            if (enemies[i]->getHealth() <= 0)
            {
                Item *cur = new Item(itemAnim, enemies[i]->getHitBox());
                items.push_back(cur);

                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                i--;
            }
        }
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AstralAvenger");
    SetTargetFPS(60);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);

    TileMap tileMap("Assets/Map/map.png", "Assets/Map/MapMatrix.dat");

    Animation *heroAnims = loadHeroAnims(6);
    Animation *mageAnims = loadMageAnims(6);
    Animation *itemAnims = loadItemAnims();

    Hero mainHero({150, 150, 32, 32}, 1280, 4, heroAnims, tileMap);
    // Mage m({250, 250, 32, 64}, 100, 3, tileMap, heroAnims, &mainHero);
    std::vector<Enemy *> enemies;
    std::vector<Item *> items;

    Camera2D camera = {0};
    camera.target = mainHero.getPositionWorld();
    camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    int frames = 0;

    while (!WindowShouldClose())
    {
        camera.target = mainHero.getPositionWorld();
        camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);
        tileMap.draw();
        mainHero.play();
        // m.play();
        if (frames % 30 == 0)
            spawnEnemies(enemies, tileMap, mageAnims, mainHero);

        if ((frames % (mainHero.getCooldownWhip() * 60)) == 0)
        {
            whipAtack(enemies, mainHero, items, *itemAnims);
        }

        playEnemies(enemies);
        playItems(items, mainHero);

        EndMode2D();
        DrawRectangle(0, 0, mainHero.getHealth(), 40, RED);
        EndDrawing();
        frames++;
    }
}
