#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "machine.h"
#include <global.h>

/*
 * 传送带
 */

namespace Belt {
extern bool placing_belt;
extern QVector<short> virtual_index;
}

class Conveyor : public Machine
{
    Q_OBJECT
    short from_direction, turing_direction;
    bool occupied;
public:
    Conveyor(int x, int y, short direction_f, short direction_t, QWidget *parent = nullptr);
    ~Conveyor();
    void show(QPainter &) const override;
    bool __is_conveyor__() const override;
    int function(Mine &) override;
    short get_enter_direction() const override;
    int save() const override;
    bool can_enter(int index) const override;
    void set_occupied(bool o);
};

void placeConveyer();

short getDirectionFromIndices(short index_1, short index_2);
short getTurnDirection(short direction_1, short direction_2);

#endif // CONVEYOR_H
