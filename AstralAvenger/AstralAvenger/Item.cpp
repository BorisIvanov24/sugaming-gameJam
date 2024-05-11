#include "Item.h"

Item::Item(const Animation &animation, const Rectangle &box, ItemType type) : animation(animation), box(box), type(type)
{
}

void Item::Draw() const
{
    animation.play({box.x, box.y});
}

const Rectangle &Item::hitBox() const
{
    return box;
}

ItemType Item::getType() const
{
    return type;
}
