#ifndef CUTTER_M_H
#define CUTTER_M_H

#include "machine.h"
#include "global.h"

/*
 * 此类为Cutter类的辅助，与Cutter类是组合关系
 */

class Cutter_M : public Machine
{
    Q_OBJECT
public:
    // QVector<Mine *> *product;
    Cutter_M(int x, int y, int direction, QWidget *parent = nullptr);
    ~Cutter_M();
    void function() override;
    int function(Mine &) override;
    bool can_enter(int) const override;

    friend bool Global::CheckJam(int index, int next_index, const Mine &ore_last);
};

#endif // CUTTER_M_H
