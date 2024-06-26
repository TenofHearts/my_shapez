#ifndef ROUND_ORE_H
#define ROUND_ORE_H

#include "mine.h"


class Round_Ore : public Mine
{
    Q_OBJECT
public:
    explicit Round_Ore(int x, int y, QWidget *parent = nullptr);
    ~Round_Ore();
    void show(QPainter &) const override;
};

#endif // ROUND_ORE_H
