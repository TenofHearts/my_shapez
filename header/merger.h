#ifndef MERGER_H
#define MERGER_H

#include "machine.h"
#include "global.h"

/*
 * 交错器，可以将两天输出轨道上的矿交替输出到同一条轨道
 */

class Merger : public Machine
{
    Q_OBJECT
    int from_bottom;
    int to_produce;
public:
    Merger(int x, int y, int direction, QWidget *parent = nullptr);
    ~Merger();
    void show(QPainter &) const override;
    void function() override;
    int function(Mine &) override;
    int save() const override;
    bool can_enter(int index) const override;
    void Abrasion() const override;
};

void placeMerger();

#endif // MERGER_H
