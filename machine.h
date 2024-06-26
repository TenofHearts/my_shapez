#ifndef MACHINE_H
#define MACHINE_H

#include "square.h"
#include <global.h>

/*
 * 该类为所有机器的基类，材质保存在Global::dest中，Global::b_dest中存放在放置时的材质
 */

namespace Device
{
    extern bool inLoop;
    extern bool placeMachine;
    extern short typeofMachine;
    extern short direction;
}

class Machine : public Square
{
    Q_OBJECT
    short direction;
    int index;

public:
    explicit Machine(int x, int y, int direction, QWidget *parent = nullptr);
    ~Machine();
    virtual int function(Mine &);
    virtual void function();
    void show(QPainter &) const override;
    int get_direction() const;
    bool __is_machine__() const override;
    virtual bool __is_conveyor__() const;
    virtual short get_enter_direction() const;
    int get_index() const override;
    int get_enter_index() const;
    virtual bool can_enter(int index) const;
    virtual void Abrasion() const;
signals:
    void erase();
};

#endif // MACHINE_H
