#include "Spawner.h"

Spawner::Spawner(Camera2D* camera, TileMap* tileMap): camera(camera), tileMap(tileMap)
{

}

void Spawner::setMaxNumberOfEnemies(unsigned maxNumberOfEnemies)
{
	this->maxNumberOfEnemies = maxNumberOfEnemies;
}

unsigned Spawner::getEnemiesCount() const
{
	//return enemies.getSize();
}

void Spawner::spawnNumberOfEnemies(unsigned numberOfEnemiesToSpawn)
{
	if ((numberOfEnemiesToSpawn + getEnemiesCount()) >= maxNumberOfEnemies)
		return;

	srand(time(0));

	for (int i = 0; i < numberOfEnemiesToSpawn; i++)
	{
		EnemyType enemyToSpawn = (EnemyType)(rand() % 3);

		switch (enemyToSpawn)
		{
			case EnemyType::MAGE:
			{
				//Enemy* ptr = new Mage();
				//enemies.push_back(ptr);
				break;
			}
			case EnemyType::SKELETON:
			{
				//Enemy* ptr = new Skeleton();
				//enemies.push_back(ptr);
				break;
			}
			case EnemyType::ASSASSIN:
			default:
			{
				//Enemy* ptr = new Assassin();
				//enemies.push_back(ptr);
				break;
			}
		}
	}
	
}

void Spawner::despawnDeadEnemies()
{
	for (int i = 0; i < getEnemiesCount(); i++)
	{
		if (enemies[i]->(!isAlive()))
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}
}
