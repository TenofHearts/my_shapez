#include "header/machine.h"

bool Device::inLoop = false;
bool Device::placeMachine = false;
short Device::typeofMachine = 0;
short Device::direction = LEFT;

Machine::Machine(int x, int y, int direct, QWidget *parent)
    : Square(x, y, parent, false), direction(direct)
{
    index = Global::getIndex(x, y);
}

Machine::~Machine()
{}

int Machine::function(Mine &)
{
    /*
     * 该机器对矿物的功能
     *
     * 返回值为0时代表不需要删除该矿物，返回值为1时代表需要删除该矿物
     */
    return 0;
}

void Machine::function()
{
    /*该机器主动的功能*/
}

void Machine::show(QPainter &) const
{}

int Machine::get_direction() const
{
    /*返回该机器的方向*/
    return direction;
}

bool Machine::__is_machine__() const
{
    return true;
}

bool Machine::__is_conveyor__() const
{
    /*返回某机器是否时传送带*/
    return false;
}

short Machine::get_enter_direction() const
{
    /*返回上一个地块的方向*/
    return (direction + 2) % 4;
}

int Machine::get_index() const
{
    /*获得地块的index*/
    return index;
}

int Machine::get_enter_index() const
{
    /*获得该机器上一个地块的index*/
    return Global::getIndexinDirection(index, get_enter_direction());
}

bool Machine::can_enter(int index) const
{
    /*返回index处的机器能否输入该机器*/
    return index == get_enter_index();
}

void Machine::Abrasion() const
{
    /*
     * 在机器function()函数或function(Mine &)函数被调用时被调用
     * 表示机器磨损消耗的成本
     *
     * 可能在后续版本中删除
     */
}