#ifndef TRASHCAN_H
#define TRASHCAN_H

#include "machine.h"
#include <global.h>

/*
 * 垃圾桶，无条件删除所有矿
 */

class Trashcan : public Machine
{
    Q_OBJECT
public:
    Trashcan(int x, int y, QWidget *parent = nullptr);
    ~Trashcan();
    void show(QPainter &) const override;
    int function(Mine &) override;
    int save() const override;
    bool can_enter(int index) const override;
    void Abrasion() const override;
};

void placeTrashcan();

#endif // TRASHCAN_H
