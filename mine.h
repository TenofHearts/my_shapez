#ifndef MINE_H
#define MINE_H

#include "square.h"

/*
 * 该类表示所有开采出的矿，材质保存在Global::ore_dest中
 */

class Mine : public Square
{
    Q_OBJECT
    bool seperable;
    int type;
    int last_index;

public:
    explicit Mine(int x, int y, int type, QWidget *parent = nullptr);
    explicit Mine(int index, int type, QWidget *parent = nullptr);
    ~Mine();
    bool is_seperable() const;
    void __set_seperable__(bool s);
    void show(QPainter &) const override;
    short get_type() const;
    double calc_distance(const Square *other) const;
    int get_index() const override;
    void Delete();
    bool __del__() const;

    friend void action(QVector<Mine *> &);
};

void action(QVector<Mine *> &);

#endif // MINE_H
