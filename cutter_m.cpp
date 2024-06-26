#include "cutter_m.h"
#include <mine.h>
#include <gamescene.h>

Cutter_M::Cutter_M(int x, int y, int direction, QWidget *parent):
    Machine(x,y,direction, parent)
{}

Cutter_M::~Cutter_M()
{}

void Cutter_M::function()
{
    int offset = EDGE_LEN / 2 - Global::conveyor_speed;
    int dir = (get_direction() + 2) % 4;
    int next_index = Global::getIndexinDirection(get_index(), get_direction());
    int delta_x = (1 - (dir & 1)) * (dir >> 1 ? 1 : -1) * offset;
    int delta_y = (dir & 1) * (dir >> 1 ? 1 : -1) * offset;
    if (Global::map[next_index] && Global::map[next_index]->__is_machine__() && static_cast<Machine *>(Global::map[next_index])->can_enter(get_index()))
    {
        Mine *temp = new Mine(Global::getXFromIndex(next_index) + delta_x, Global::getYFromIndex(next_index) + delta_y, RIGHT_HALF, Global::game);
        Global::all_mine_vec.push_back(temp);
    }
}

int Cutter_M::function(Mine &ore)
{
    if (ore.get_type() == RIGHT_HALF)
    {
        int delta_x = (1 - (get_direction() & 1)) * ((get_direction() >> 1) ? 1 : -1) * Global::conveyor_speed;
        ore.getx() += delta_x;
        int delta_y = (get_direction() & 1) * ((get_direction() >> 1) ? 1 : -1) * Global::conveyor_speed;
        ore.gety() += delta_y;

        return 0;
    }
    else
    {
        return 0;
    }
}

bool Cutter_M::can_enter(int) const
{
    return false;
}