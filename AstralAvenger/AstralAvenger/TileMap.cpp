#include "TileMap.h"
#include <fstream>

TileMap::TileMap(const char* filePathBackground, const char* filePathMatrix)
{
	background = LoadTexture(filePathBackground);

	if (!filePathMatrix)
	{
		return;
	}

	std::ifstream ifs(filePathMatrix, std::ios::binary | std::ios::in);

	ifs.read((char*)matrix, MAP_WIDTH * MAP_HEIGHT * sizeof(unsigned));
}

int8_t TileMap::getValueAt(unsigned row, unsigned col) const
{
	return matrix[row][col];
}

void TileMap::setValueAt(unsigned row, unsigned col, int8_t value)
{
	matrix[row][col] = value;
}

void TileMap::draw() const
{
	DrawTexture(background, 0, 0, RAYWHITE);
}
