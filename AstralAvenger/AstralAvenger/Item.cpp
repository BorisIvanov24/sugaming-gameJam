#include "Item.h"

Item::Item(const Animation &animation, const Rectangle &box) : animation(animation), box(box)
{
}

void Item::Draw() const
{
    animation.play({box.x, box.y});
}

const Rectangle& Item::hitBox() const
{
    return box;
}
