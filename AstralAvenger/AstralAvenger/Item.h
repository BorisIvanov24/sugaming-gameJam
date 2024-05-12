#pragma once
#include "Animation.h"
constexpr Rectangle DEFAULT_ITEM_REC = {32, 32, 0, 0};

enum class ItemType
{
    STAR,
    HEART,
    ENGINE,
    CABINE,
    CAPSULE,
    FUEL_TANK
};

class Item
{
  public:
    Item() = default;
    Item(const Animation &animation, const Rectangle &box, ItemType type);
    void Draw() const;
    const Rectangle &hitBox() const;
    ItemType getType() const;

  private:
    Animation animation;
    Rectangle box = DEFAULT_ITEM_REC;
    ItemType type;
};
