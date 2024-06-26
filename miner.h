#ifndef MINER_H
#define MINER_H

#include "machine.h"
#include <global.h>
#include <mine_place.h>

/*
 * 采矿机
 */

class Miner : public Machine
{
    Q_OBJECT
    int type;
public:
    Miner(int x, int y, int direction, int type, QWidget *parent = nullptr);
    ~Miner();
    void show(QPainter &) const override;
    short get_type() const;
    void function() override;
    int function(Mine &) override;
    int save() const override;
    bool can_enter(int) const override;
    void Abrasion() const override;

    friend bool Global::CheckJam(int index, int next_index, const Mine &ore_last);
};

void placeMiner();

#endif // MINER_H
