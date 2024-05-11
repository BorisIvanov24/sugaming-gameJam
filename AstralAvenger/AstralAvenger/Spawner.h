#pragma once
#include "Enemy.h"
#include <vector>
#include "raylib.h"
#include "TileMap.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

enum class EnemyType
{
	ASSASSIN,
	MAGE,
	SKELETON
};

class Spawner
{
public:
	Spawner() = default;
	Spawner(Camera2D* camera, TileMap* tileMap);

	void setMaxNumberOfEnemies(unsigned maxNumberOfEnemies);
	unsigned getEnemiesCount() const;
	void spawnNumberOfEnemies(unsigned numberOfEnemies);
	void despawnDeadEnemies();

private:
	std::vector<Enemy*> enemies;
	Camera2D* camera = nullptr;
	TileMap* tileMap = nullptr;
	unsigned maxNumberOfEnemies = 5;

};

