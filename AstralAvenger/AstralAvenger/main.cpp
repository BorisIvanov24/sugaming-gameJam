#include "raylib.h"
#include <iostream>
#include "TileMap.h"


const unsigned SCREEN_WIDTH = 1280;
const unsigned SCREEN_HEIGHT = 720;

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AstralAvenger");
	SetTargetFPS(60);

	TileMap tileMap("Assets/Map/map.png", nullptr);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		tileMap.draw();

		EndDrawing();
	}
}