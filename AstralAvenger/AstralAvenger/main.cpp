#include "Constants.h"
#include "Enemy.h"
#include "Hero.h"
#include "Item.h"
#include "Mage.h"
#include "MyTime.h"
#include "TextBox.h"
#include "TileMap.h"
#include "UIButton.h"
#include "raylib.h"
#include <iostream>
#include <sstream>
#include <vector>
#pragma warning(disable : 4996)

int starsCount = 0;
int enemiesKilled = 0;
int potionsCollected = 0;
int liveEnemies = 0;

int engine = 0;
int fuelTank = 0;
int capsule = 0;
int cabine = 0;
Time myTime(0, 0, 0);

bool hitboxesOn = false;
bool statsOn = true;

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

Animation *loadSpecItems(unsigned count)
{
    Animation *res = new Animation[count];
    res[0].addTexture(LoadTexture("Assets/Rocket/rocket_0.png")); // cabine
    res[1].addTexture(LoadTexture("Assets/Rocket/rocket_1.png")); // tank
    res[2].addTexture(LoadTexture("Assets/Rocket/rocket_2.png")); // capsula
    res[3].addTexture(LoadTexture("Assets/Rocket/rocket_3.png")); // engine

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
    liveEnemies++;
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
                potionsCollected++;
                break;
            case ItemType::ENGINE:
                engine++;
                break;
            case ItemType::CABINE:
                cabine++;
                break;
            case ItemType::CAPSULE:
                capsule++;
                break;
            case ItemType::FUEL_TANK:
                fuelTank++;
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
               const Animation &heartAnim, const Animation *specItemsAnims)
{

    srand(time(0));
    for (int i = 0; i < enemies.size(); i++)
    {
        if (CheckCollisionRecs(hero.getWhipRec(), enemies[i]->getHitBox()))
        {

            enemies[i]->takeDamage(hero.getDamage());
            if (enemies[i]->getHealth() <= 0)
            {
                int ran = (rand() % 420);
                int chanceX = starsCount / 100;
                if (chanceX > 60)
                    chanceX = 60;

                ItemType type = ItemType::CABINE;

                if (ran < 60)
                    type = ItemType::HEART;
                else if (ran < 420 - chanceX * 4)
                    type = ItemType::STAR;
                else if (ran < 420 - chanceX * 3)
                    type = ItemType::ENGINE;
                else if (ran < 420 - chanceX * 2)
                    type = ItemType::CABINE;
                else if (ran < 420 - chanceX * 1)
                    type = ItemType::CAPSULE;
                else
                    type = ItemType::FUEL_TANK;

                ItemType curType = type;
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
                case ItemType::ENGINE:
                    anim = &specItemsAnims[3];
                    break;
                case ItemType::FUEL_TANK:
                    anim = &specItemsAnims[1];
                    break;
                case ItemType::CABINE:
                    anim = &specItemsAnims[0];
                    break;
                case ItemType::CAPSULE:
                    anim = &specItemsAnims[2];
                    break;
                default:
                    break;
                }

                Item *cur = new Item(*anim, enemies[i]->getHitBox(), curType);
                items.push_back(cur);

                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                enemiesKilled++;
                liveEnemies--;
                i--;
            }
        }
    }
}

void writeCoins(Font &font)
{
    char str[19] = "Stars ";
    char num[11] = {0};
    strcat(str, itoa(starsCount, num, 10));
    TextBox tb(str, {10, 40, 120, 50}, font, YELLOW);
    tb.draw();
}

void drawHealth(const Hero &hero, const Font &font)
{
    DrawRectangle(0, 0, hero.getHealth(), 40, RED);
    char str[16] = "Health ";
    char num[6];
    itoa(hero.getHealth(), num, 10);
    strcat(str, num);
    TextBox tb(str, {0, 0, 180, 50}, font, BLACK);
    tb.draw();
}

void writeItems(const Font &font)
{
    char str[21] = "PotionsDrunk ";
    char num[6];
    itoa(potionsCollected, num, 10);
    strcat(str, num);
    TextBox tb(str, {0, 70, 230, 50}, font, YELLOW);
    tb.draw();

    char str1[23] = "Enemies killed ";
    char num1[6];
    itoa(enemiesKilled, num1, 10);
    strcat(str1, num1);
    TextBox tb1(str1, {0, 100, 250, 50}, font, YELLOW);
    tb1.draw();

    char str2[23] = "Enemies alive ";
    char num2[6];
    itoa(liveEnemies, num2, 10);
    strcat(str2, num2);
    TextBox tb2(str2, {550, 40, 250, 50}, font, YELLOW);
    tb2.draw();

    char str3[15] = "Engine ";
    char num3[6];
    itoa(engine, num3, 10);
    strcat(str3, num3);
    TextBox tb3(str3, {15, 130, 120, 50}, font, engine ? GREEN : ORANGE);
    tb3.draw();

    char str4[18] = "FuelTank ";
    char num4[6];
    itoa(fuelTank, num4, 10);
    strcat(str4, num4);
    TextBox tb4(str4, {10, 160, 150, 50}, font, fuelTank ? GREEN : ORANGE);
    tb4.draw();

    char str5[18] = "Cabin ";
    char num5[6];
    itoa(cabine, num5, 10);
    strcat(str5, num5);
    TextBox tb5(str5, {10, 190, 105, 50}, font, cabine ? GREEN : ORANGE);
    tb5.draw();

    char str6[18] = "Capsule ";
    char num6[6];
    itoa(capsule, num6, 10);
    strcat(str6, num6);
    TextBox tb6(str6, {10, 220, 150, 50}, font, capsule ? GREEN : ORANGE);
    tb6.draw();
}

void printTime(const Font &font)
{
    // timer
    char time[16] = "Time: ";
    char t[10];
    std::stringstream sstr;
    myTime.serialize(sstr);

    strcpy(t, sstr.str().c_str());
    strcat(time, t);
    time[14] = '\0'; // remove everything not needed
    TextBox timeBox(time, {900, 25, 210, 70}, font, YELLOW);
    timeBox.draw();
}

enum class screenState
{
    MAIN_MENU,
    GAME,
    GAME_OVER,
    WIN
};

int main()
{
    screenState scrState = screenState::MAIN_MENU;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AstralAvenger  Press H to turn on hitboxes, Press T to hide stats");
    SetTargetFPS(60);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);

    UIButton buttonPlay({510, 510, 250, 90}, "Assets/Menu/buttonPlayTexture.png", "Play");
    Font font = LoadFont("Assets/Menu/RACESPACEREGULAR.otf");
    buttonPlay.setFont(font);
    Image icon = LoadImage("Assets/Star/star_0.png");

    UIButton buttonPlayAgain({510, 510, 250, 90}, "Assets/Menu/buttonPlayTexture.png", "Try Again");
    buttonPlayAgain.setFont(font);

    UIButton buttonContinue({330, 510, 250, 90}, "Assets/Menu/buttonPlayTexture.png", "Continue");
    buttonContinue.setFont(font);

    UIButton buttonExit({630, 510, 250, 90}, "Assets/Menu/buttonPlayTexture.png", "Exit");
    buttonExit.setFont(font);

    Texture2D
        mainMenuBackground; //("Assets/Menu/mainMenuBackground.png", { 0, 0, GetScreenWidth(), GetScreenHeight()});
    mainMenuBackground = LoadTexture("Assets/Menu/mainMenuBackground.png");
    Texture2D gameOverBackground;
    gameOverBackground = LoadTexture("Assets/Menu/gameOverBackground.png");

    Texture2D winBackground;
    winBackground = LoadTexture("Assets/Menu/winScreen.png");

    TileMap tileMap("Assets/Map/map.png", "Assets/Map/MapMatrix.dat");

    Animation *heroAnims = loadHeroAnims(6);
    Animation *mageAnims = loadMageAnims(6);
    Animation *skeletonAnims = loadSkeletonAnims(8);
    Animation *assassinAnims = loadAsassinAnims(8);
    Animation *starAnims = loadStarAnims();
    Animation *heartAnims = loadHeartAnims();
    Animation *specItems = loadSpecItems(4);

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

    SetWindowIcon(icon);

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_H))
        {
            mainHero.setHitBoxes();
            Enemy::hitboxesOn = !Enemy::hitboxesOn;
        }
        else if (IsKeyPressed(KEY_T))
        {
            statsOn = !statsOn;
        }

        switch (scrState)
        {
        case screenState::MAIN_MENU: {
            BeginDrawing();
            DrawTexture(mainMenuBackground, 0, 0, RAYWHITE);
            buttonPlay.play();
            if (buttonPlay.isClicked())
                scrState = screenState::GAME;

            EndDrawing();
            break;
        }
        case screenState::GAME: {
            if (frames % 60 == 0)
                myTime.tick();

            camera.target = mainHero.getPositionWorld();
            camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

            if (engine && cabine && fuelTank && capsule)
                scrState = screenState::WIN;

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
                whipAtack(enemies, mainHero, items, *starAnims, *heartAnims, specItems);
            }

            playEnemies(enemies);

            // std::cout << mainHero.getHealth() << std::endl;
            if (mainHero.getHealth() > 1280)
            {
                scrState = screenState::GAME_OVER;
            }

            playItems(items, mainHero);

            EndMode2D();

            drawHealth(mainHero, font);
            if (statsOn)
            {
                writeCoins(font);
                writeItems(font);
                printTime(GetFontDefault());
            }
            // DrawFPS(1200, 50);

            EndDrawing();
            frames++;
            break;
        }
        case screenState::GAME_OVER: {
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
                enemiesKilled = 0;
                potionsCollected = 0;
                liveEnemies = 0;

                engine = 0;
                fuelTank = 0;
                capsule = 0;
                cabine = 0;
                myTime.restart();
            }

            EndDrawing();
            break;
        }
        case screenState::WIN: {
            BeginDrawing();
            DrawTexture(winBackground, 0, 0, RAYWHITE);
            buttonContinue.play();
            buttonExit.play();

            if (buttonContinue.isClicked())
                scrState = screenState::GAME;
            else if (buttonExit.isClicked())
                return 0;
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
