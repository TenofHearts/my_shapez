#include "header/mine.h"
#include "header/machine.h"
#include <header/conveyor.h>

Mine::Mine(int x, int y, int type, QWidget *parent)
    : Square(x, y, parent)
    , type(type)
{
    last_index = get_index();

    if (type == ROUND)
    {
        seperable = true;
    }
    else
    {
        seperable = false;
    }
}

Mine::Mine(int index, int type, QWidget *parent)
    : Square(index, parent)
    , type(type)
{}

Mine::~Mine()
{}

bool Mine::is_seperable() const
{
    /*Returns whether a kind of mine is seperable*/
    return seperable;
}

void action(QVector<Mine *> &vec)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](Mine *ore){
        int index = ore->get_index();
        if (Global::map[index] && Global::map[index]->__is_machine__())
        {
            if (static_cast<Machine *>(Global::map[index])->function(*ore))
                ore->Delete();
        }
        else if(Global::map[index] == nullptr || Global::map[index]->__is_mine__())
        {
            ore->Delete();
        }
        return ore->__del__();
        }), vec.end());
}

void Mine::__set_seperable__(bool s)
{
    seperable = s;
}

void Mine::show(QPainter &painter) const
{
    painter.drawPixmap(X(), Y(), EDGE_LEN, EDGE_LEN, QPixmap(Global::ore_dest[type]));
}

short Mine::get_type() const
{
    return type;
}

double Mine::calc_distance(const Square *other) const
{
    if (other)
    {
        int x1, x2, y1, y2;
        getCenter(x1, y1);
        other->getCenter(x2, y2);
        return std::sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
    else
        return 0;
}

int Mine::get_index() const
{
    int x, y;
    getCenter(x, y);
    return Global::getIndex(x, y);
}

void Mine::Delete()
{
    type = DELETE;
}

bool Mine::__del__() const
{
    return type == DELETE;
}