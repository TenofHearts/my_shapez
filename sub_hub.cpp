#include "sub_hub.h"
#include <mine.h>

Sub_Hub::Sub_Hub(int i, QWidget *parent): Machine(Global::getXFromIndex(i), Global::getYFromIndex(i), 0, parent)
{}

Sub_Hub::~Sub_Hub()
{}

bool Sub_Hub::can_enter(int) const
{
    return true;
}

int Sub_Hub::function(Mine &ore)
{
    /*若ore符合要求，则获得报酬，否则得到罚款*/
    if (Level::goal[ore.get_type()] > Level::cur[ore.get_type()])
    {
        Global::coin_num += Global::ore_price;
        Level::cur[ore.get_type()]++;
    }
    else
    {
        if (Global::coin_num >= 2)
        {
            Global::coin_num -= 2;
        }
    }
    return 1;
}