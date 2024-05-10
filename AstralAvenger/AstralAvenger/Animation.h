#pragma once
#include "raylib.h"
#include <vector>
#include "PictureBox.h"

const uint8_t CHANGE_FRAME_AFTER =5;

enum class AnimationType
{
    DEFAULT,
    MOVE_DOWN,
    MOVE_UP,
    MOVE_LEFT,
    MOVE_RIGHT,
    ITEM
};
class Animation
{
  public:
    Animation() = default;
    Animation(const Texture2D *textures, unsigned size, const Rectangle& rec);
    unsigned getTexturesCount() const;
    void loadFromFolder(const char *path, uint8_t numberOfTextures);
    void play(const Vector2& posToPlay) const;
    void addTexture(const Texture2D &texture);
    void removeLastTexture(uint8_t index);

  private:
    std::vector<PictureBox> textures;
    mutable uint8_t currentTexture = 0;
    mutable uint8_t frames;
    Rectangle rec = { 30, 30, 32, 32 };
};
