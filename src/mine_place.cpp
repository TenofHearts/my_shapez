#include "mine_place.h"

Mine_Place::Mine_Place(int x, int y, int type, QWidget *parent):
    Square(x, y, parent, true), type(type)
{}

Mine_Place::Mine_Place(int index, int type, QWidget *parent):
    Square(Global::getXFromIndex(index), Global::getYFromIndex(index), parent, true), type(type)
{}

Mine_Place::~Mine_Place()
{}

short Mine_Place::get_type() const
{
    return type;
}

bool Mine_Place::__is_mine__() const
{
    return true;
}

bool Mine_Place::is_seperable() const
{
    return !type;
}

int Mine_Place::save() const
{
    return MINING_PLACE | (type << TYPE_DIGITS);
}
