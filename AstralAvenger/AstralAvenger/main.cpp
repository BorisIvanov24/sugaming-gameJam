#include "Constants.h"
#include "Enemy.h"
#include "Hero.h"
#include "Mage.h"
#include "Spawner.h"
#include "TileMap.h"
#include "raylib.h"
#include <iostream>
#include <vector>

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

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AstralAvenger");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    TileMap tileMap("Assets/Map/map.png", "Assets/Map/MapMatrix.dat");

    Animation *heroAnims = loadHeroAnims(5);
    Hero mainHero({150, 150, 32, 64}, 100, 5, heroAnims, tileMap);
    Mage m({250, 250, 32, 64}, 100, 3, tileMap, heroAnims, &mainHero);

    Camera2D camera = {0};
    camera.target = mainHero.getPositionWorld();
    camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    while (!WindowShouldClose())
    {
        camera.target = mainHero.getPositionWorld();
        camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);
        tileMap.draw();
        mainHero.play();
        m.play();

        EndMode2D();

        EndDrawing();
    }
}
