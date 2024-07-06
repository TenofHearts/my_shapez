#ifndef ROTATER_H
#define ROTATER_H

#include "machine.h"
#include "global.h"

/*
 * 旋转器，就是旋转180°，只对切割后的矿有效果，但是什么类型的矿都能输入
 */

class Rotater : public Machine
{
    Q_OBJECT
    int to_produce;
public:
    Rotater(int x, int y, int direction, QWidget *parent = nullptr);
    ~Rotater();
    void show(QPainter &) const override;
    void function() override;
    int function(Mine &) override;
    int save() const override;
    bool can_enter(int index) const override;
    void Abrasion() const override;
};

void placeRotater();

#endif // ROTATER_H
