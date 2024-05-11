#include "Constants.h"
#include "Hero.h"
#include "TileMap.h"
#include "raylib.h"
#include <iostream>

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

    for (int i = 0; i < 128; i++)
    {
        std::cout << std::endl;
        for (int j = 0; j < 128; j++)
        {
            std::cout << (int)tileMap.getValueAt(i, j);
        }
    }
    Animation *heroAnims = loadHeroAnims(5);
    Hero mainHero({150, 150, 32, 64}, 100, 5, heroAnims, tileMap);

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
        EndMode2D();

        EndDrawing();
    }
}
