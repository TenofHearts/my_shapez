#include "conveyor.h"
#include "gamescene.h"
#include <cmath>
#include <algorithm>
// #include <iostream>
#include "mine.h"

bool Belt::placing_belt = false;
QVector<short> Belt::virtual_index;

Conveyor::Conveyor(int x, int y, short direction_f, short direction_t, QWidget *parent):
    Machine(x, y, direction_t, parent), from_direction(direction_f)
{
    occupied = false;

    turing_direction = getTurnDirection(direction_f, direction_t);

    Conveyor::connect(this, &Conveyor::erase, [=](){
        if (Global::map[Global::getIndex(x, y)])
        {
            delete Global::map[Global::getIndex(x, y)];
            Global::map[Global::getIndex(x, y)] = nullptr;
        }
    });
}

Conveyor::~Conveyor()
{}

void placeConveyer()
{
    QTimer *timer = new QTimer;
    timer->start(40);
    GameScene::connect(timer, &QTimer::timeout, [=]()
                       {
                           Global::game->update();
                       });

    Device::inLoop = true;
    Device::placeMachine = false;
    Device::typeofMachine = CONVEYOR;
    while (Device::inLoop)
    {
        Global::game->setMouseTracking(true);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    }
    if (Device::placeMachine)
    {

        if (Belt::virtual_index.size() > 1)
        {
            short last_direction = getDirectionFromIndices(Belt::virtual_index[0], Belt::virtual_index[1]);
            if (Global::map[Belt::virtual_index[0]] == nullptr)
            {
                Global::map[Belt::virtual_index[0]] = new Conveyor(Global::getXFromIndex(Belt::virtual_index[0]), Global::getYFromIndex(Belt::virtual_index[0]), last_direction, last_direction, Global::game);
            }

            for (int i = 1; i < Belt::virtual_index.size() - 1; ++i)
            {
                int index = Belt::virtual_index[i];
                short current_direction = getDirectionFromIndices(Belt::virtual_index[i], Belt::virtual_index[i + 1]);
                if (Global::map[index] == nullptr)
                {
                    Global::map[index] = new Conveyor(Global::getXFromIndex(index), Global::getYFromIndex(index), last_direction, current_direction, Global::game);
                }
                last_direction = current_direction;
            }

            if (Global::map[Belt::virtual_index.last()] == nullptr)
            {
                Global::map[Belt::virtual_index.last()] = new Conveyor(Global::getXFromIndex(Belt::virtual_index.last()), Global::getYFromIndex(Belt::virtual_index.last()), last_direction, last_direction, Global::game);
            }
        }
    }
    delete timer;
    Belt::placing_belt = false;
    Belt::virtual_index.clear();
    Device::placeMachine = false;
    Device::typeofMachine = 0;
}

short getDirectionFromIndices(short index_1, short index_2)
{
    short diff = index_2 - index_1;
    return diff % NUM_OF_HORIZONTAL_GRIDS + abs(diff / NUM_OF_HORIZONTAL_GRIDS)  + diff / NUM_OF_HORIZONTAL_GRIDS + 1;
}

short getTurnDirection(short direction_1, short direction_2)
{
    switch ((direction_2 - direction_1 + 4) % 4)
    {
    case 3:
        return TURN_LEFT;
    case 1:
        return TURN_RIGHT;
    case 0:
        return TURN_STRAIGHT;
    default:
        return 0;
    }
}

void Conveyor::show(QPainter &painter) const
{
    QTransform transform;
    transform.rotate((from_direction + 2) % 4 * 90);

    painter.drawPixmap(X(), Y(), EDGE_LEN, EDGE_LEN, QPixmap(Global::belt_dest[turing_direction]).transformed(transform));
}

bool Conveyor::__is_conveyor__() const
{
    return true;
}

int Conveyor::function(Mine &ore)
{
    set_occupied(true);

    if (from_direction == get_direction())
    {
        if (from_direction % 2)
        {
            ore.getx() = Global::getXFromIndex(get_index());
        }
        else
        {
            ore.gety() = Global::getYFromIndex(get_index());
        }
    }
    int next_index = Global::getIndexinDirection(get_index(), get_direction());
    int x, y;
    ore.getCenter(x, y);
    int delta_x = ((1 - (from_direction & 1)) * ((from_direction >> 1) ? 1 : -1) + (1 - (get_direction() & 1)) * ((get_direction() >> 1) ? 1 : -1)) * Global::conveyor_speed / 2;
    int delta_y = ((from_direction & 1) * ((from_direction >> 1) ? 1 : -1) + (get_direction() & 1) * ((get_direction() >> 1) ? 1 : -1)) * Global::conveyor_speed / 2;
    if (Global::getIndex(x + delta_x, y + delta_y) == get_index())
    {
        ore.getx() += delta_x;
        ore.gety() += delta_y;
    }
    else if (Global::map[next_index] && Global::map[next_index]->__is_machine__() && static_cast<Machine *>(Global::map[next_index])->can_enter(get_index()))
    {
        ore.getx() += delta_x;
        ore.gety() += delta_y;
        set_occupied(false);
    }

    return 0;
}

short Conveyor::get_enter_direction() const
{
    return (from_direction + 2) % 4;
}

int Conveyor::save() const
{
    return CONVEYOR | (from_direction << TYPE_DIGITS) | (get_direction() << (TYPE_DIGITS + DIRECTION_DIGITS));
}

bool Conveyor::can_enter(int index) const
{
    return !occupied && index == get_enter_index();
}

void Conveyor::set_occupied(bool o)
{
    occupied = o;
}