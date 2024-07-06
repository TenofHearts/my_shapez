#ifndef CUTTER_H
#define CUTTER_H

#include "machine.h"
#include "global.h"
#include "cutter_m.h"

/*
 * 切割机
 */

class Cutter_M;

class Cutter : public Machine
{
    Q_OBJECT
    Cutter_M *sub_cutter;
    int to_produce = 0;
public:
    Cutter(int x, int y, int direction, QWidget *parent = nullptr);
    ~Cutter();
    void show(QPainter &) const override;
    short get_enter_direction() const override;
    int save() const override;
    void function() override;
    int function(Mine &) override;
    bool can_enter(int index) const override;
    void Abrasion() const override;
signals:
    void output();

    friend bool Global::CheckJam(int index, int next_index, const Mine &ore_last);
};

void placeCutter();

#endif // CUTTER_H
