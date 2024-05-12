#include "Constants.h"
#include "Enemy.h"
#include "Hero.h"
#include "Item.h"
#include "Mage.h"
#include "TextBox.h"
#include "TileMap.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include "UIButton.h"
#pragma warning(disable : 4996)

int starsCount = 0;
bool hitboxesOn = false;

Animation *loadHeroAnims(unsigned count)
{
    Animation *res = new Animation[count];
    res[(int)AnimationType::DEFAULT].loadFromFolder("Assets/Hero/walkRight/walkRight_", 1);
    res[(int)AnimationType::MOVE_UP].loadFromFolder("Assets/Hero/walkUp/walkUp_", 8);
    res[(int)AnimationType::MOVE_LEFT].loadFromFolder("Assets/Hero/walkLeft/walkLeft_", 8);
    res[(int)AnimationType::MOVE_RIGHT].loadFromFolder("Assets/Hero/walkRight/walkRight_", 8);
    res[(int)AnimationType::MOVE_DOWN].loadFromFolder("Assets/Hero/walkRight/walkRight_", 8);
    res[5].setRectangle({0, 0, 160, 64});
    res[5].loadFromFolder("Assets/Hero/whip/whip_", 7);

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

Animation *loadSkeletonAnims(unsigned count)
{
    Animation *res = new Animation[count];
    res[(int)AnimationType::DEFAULT].loadFromFolder("Assets/Skeleton/skeletonWalkRight/skeletonWalkRight_", 1);
    res[(int)AnimationType::MOVE_UP].loadFromFolder("Assets/Skeleton/skeletonWalkRight/skeletonWalkRight_", 8);
    res[(int)AnimationType::MOVE_LEFT].loadFromFolder("Assets/Skeleton/skeletonWalkLeft/skeletonWalkLeft_", 8);
    res[(int)AnimationType::MOVE_RIGHT].loadFromFolder("Assets/Skeleton/skeletonWalkRight/skeletonWalkRight_", 8);
    res[(int)AnimationType::MOVE_DOWN].loadFromFolder("Assets/Skeleton/skeletonWalkLeft/skeletonWalkLeft_", 8);
    res[(int)AnimationType::HURT].loadFromFolder("Assets/Skeleton/skeletonHurt/skeletonHurt_", 8);
    return res;
}

Animation *loadAsassinAnims(unsigned count)
{
    Animation *res = new Animation[count];
    res[(int)AnimationType::DEFAULT].loadFromFolder("Assets/Assassin/assassinWalkRight/assassinWalkRight_", 1);
    res[(int)AnimationType::MOVE_UP].loadFromFolder("Assets/Assassin/assassinWalkRight/assassinWalkRight_", 6);
    res[(int)AnimationType::MOVE_LEFT].loadFromFolder("Assets/Assassin/assassinWalkLeft/assassinWalkLeft_", 6);
    res[(int)AnimationType::MOVE_RIGHT].loadFromFolder("Assets/Assassin/assassinWalkRight/assassinWalkRight_", 6);
    res[(int)AnimationType::MOVE_DOWN].loadFromFolder("Assets/Assassin/assassinWalkLeft/assassinWalkLeft_", 6);
    res[(int)AnimationType::HURT].loadFromFolder("Assets/Assassin/assassinHurt/assassinHurt_", 6);
    return res;
}

Animation *loadStarAnims()
{
    Animation *res = new Animation;
    res->loadFromFolder("Assets/Star/star_", 6);

    return res;
}
Animation *loadHeartAnims()
{
    Animation *res = new Animation;
    res->loadFromFolder("Assets/potion/potion_", 4);

    return res;
}

void spawnEnemies(std::vector<Enemy *> &enemies, const TileMap &tilemap, const Animation *animMage,
                  const Animation *animSkeleton, const Animation *animAssassin, Hero &hero)
{
    // 3
    int ran = rand() % 3;
    const Animation *anim = nullptr;
    switch (ran)
    {
    case 0:
        anim = animMage;
        break;
    case 1:
        anim = animSkeleton;
        break;
    case 2:
        anim = animAssassin;
    default:
        break;
    }

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

void playItems(std::vector<Item *> &items, Hero &hero)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (CheckCollisionRecs(hero.getHitBox(), items[i]->hitBox()))
        {

            switch (items[i]->getType())
            {
            case ItemType::STAR:
                starsCount++;
                break;
            case ItemType::HEART:
                hero.heal();
                break;
            default:
                break;
            }
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

void whipAtack(std::vector<Enemy *> &enemies, const Hero &hero, std::vector<Item *> &items, const Animation &starAnim,
               const Animation &heartAnim)
{

    srand(time(0));
    for (int i = 0; i < enemies.size(); i++)
    {
        if (CheckCollisionRecs(hero.getWhipRec(), enemies[i]->getHitBox()))
        {

            enemies[i]->takeDamage(hero.getDamage());
            if (enemies[i]->getHealth() <= 0)
            {
                int ran = (rand() % 10);

                if (ran < 8) // 20% for potion
                    ran = 0;
                else // 80 % for star
                    ran = 1;
                ItemType curType = (ItemType)(ran);
                // std::cout << (int)curType << std::endl;
                const Animation *anim = nullptr;
                switch (curType)
                {
                case ItemType::STAR:
                    anim = &starAnim;
                    break;
                case ItemType::HEART:
                    anim = &heartAnim;
                    break;
                default:
                    break;
                }

                Item *cur = new Item(*anim, enemies[i]->getHitBox(), curType);
                items.push_back(cur);

                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                i--;
            }
        }
    }
}

void writeCoins(Font& font)
{
    char str[19] = "Stars ";
    char num[11] = {0};
    strcat(str, itoa(starsCount, num, 10));
    TextBox tb(str, {10, 50, 150, 150}, font, YELLOW);
    tb.draw();
}

enum class screenState
{
    MAIN_MENU,
    GAME,
    GAME_OVER
};

int main()
{
    
    screenState scrState = screenState::MAIN_MENU;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AstralAvenger    Press H to turn on hitboxes");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    UIButton buttonPlay({ 510, 510, 250, 90 }, "Assets/Menu/buttonPlayTexture.png", "Play");
    Font font = LoadFont("Assets/Menu/RACESPACEREGULAR.otf");
    buttonPlay.setFont(font);

    UIButton buttonPlayAgain({ 510, 510, 250, 90 }, "Assets/Menu/buttonPlayTexture.png", "Try Again");
    buttonPlayAgain.setFont(font);

    Texture2D mainMenuBackground;//("Assets/Menu/mainMenuBackground.png", { 0, 0, GetScreenWidth(), GetScreenHeight()});
    mainMenuBackground = LoadTexture("Assets/Menu/mainMenuBackground.png");
    Texture2D gameOverBackground;
    gameOverBackground = LoadTexture("Assets/Menu/gameOverBackground.png");

    TileMap tileMap("Assets/Map/map.png", "Assets/Map/MapMatrix.dat");

    Animation *heroAnims = loadHeroAnims(6);
    Animation *mageAnims = loadMageAnims(6);
    Animation *skeletonAnims = loadSkeletonAnims(8);
    Animation *assassinAnims = loadAsassinAnims(8);
    Animation *starAnims = loadStarAnims();
    Animation *heartAnims = loadHeartAnims();

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
            if (IsKeyPressed(KEY_H))
            {
                mainHero.setHitBoxes();
                Enemy::hitboxesOn = !Enemy::hitboxesOn;
            }


        switch (scrState)
        {
        case screenState::MAIN_MENU:
        {
            BeginDrawing();
            DrawTexture(mainMenuBackground, 0, 0, RAYWHITE);
            buttonPlay.play();
            if (buttonPlay.isClicked())
                scrState = screenState::GAME;

            EndDrawing();
            break;
        }
        case screenState::GAME:
        {
            camera.target = mainHero.getPositionWorld();
            camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

            BeginDrawing();
            ClearBackground(LIGHTGRAY);

            BeginMode2D(camera);
            tileMap.draw();
            mainHero.play();
            // m.play();
            if (frames % 30 == 0)
                spawnEnemies(enemies, tileMap, mageAnims, skeletonAnims, assassinAnims, mainHero);

            if ((frames % (mainHero.getCooldownWhip() * 60)) == 0)
            {
                mainHero.setWhipPlaying();
                whipAtack(enemies, mainHero, items, *starAnims, *heartAnims);
            }

            playEnemies(enemies);

            std::cout << mainHero.getHealth() << std::endl;
            if (mainHero.getHealth() > 1280)
            {
                scrState = screenState::GAME_OVER;
            }

            playItems(items, mainHero);

            EndMode2D();
            DrawRectangle(0, 0, mainHero.getHealth(), 40, RED);
            writeCoins(font);
            EndDrawing();
            frames++;
            break;
        }
        case screenState::GAME_OVER:
        {
            BeginDrawing();
            DrawTexture(gameOverBackground, 0, 0, RAYWHITE);
            buttonPlayAgain.play();

            if (buttonPlayAgain.isClicked())
            {
                scrState = screenState::GAME;
                
                for (int i = 0; i < enemies.size(); i++)
                {
                    delete enemies[i];
                }

                enemies.clear();

                for (int i = 0; i < items.size(); i++)
                {
                    delete items[i];
                }

                items.clear();

                mainHero.setHealth(1280);
                starsCount = 0;
            }

            EndDrawing();
            break;
        }
        }
    }

    // BeginDrawing();
    // ClearBackground(LIGHTGRAY);
    // TextBox end("Game over!", {0.f, 0.f, (float)GetScreenHeight(), (float)GetScreenWidth()}, GetFontDefault(), PINK);
    // EndDrawing();
}
