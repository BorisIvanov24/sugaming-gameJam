#pragma once
#include "Animation.h"
constexpr Rectangle DEFAULT_ITEM_REC = {32, 32, 0, 0};

class Item
{
  public:
    Item() = default;
    Item(const Animation &animation, const Rectangle &box);
    void Draw() const;
    const Rectangle &hitBox() const;

  private:
    Animation animation;
    Rectangle box = DEFAULT_ITEM_REC;
};
