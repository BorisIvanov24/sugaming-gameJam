#pragma once
#include "Constants.h"
#include "raylib.h"
#include <cinttypes>

/*
 0 -> empty block
 1 -> solid block
*/

class TileMap
{
  public:
    TileMap() = default;
    TileMap(const char *filePathBackground, const char *filePathMatrix);

    int8_t getValueAt(unsigned col, unsigned row) const;
    void setValueAt(unsigned col, unsigned row, int8_t value);

    void draw() const;

  private:
    Texture2D background = {0};
    int8_t matrix[MAP_WIDTH][MAP_HEIGHT] = {0};
};
