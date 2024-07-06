#ifndef MINE_PLACE_H
#define MINE_PLACE_H

#include "square.h"
#include "global.h"

/*
 * 此类为采矿点的类，在地图中固定，不能放置，不能删除
 * (其实就是我想偷点懒~希望善良的助教gg放过)
 */

class Mine_Place : public Square
{
    Q_OBJECT
    short type;
public:
    Mine_Place(int x, int y, int type, QWidget *parent = nullptr);
    Mine_Place(int index, int type, QWidget *parent = nullptr);
    ~Mine_Place();
    short get_type() const;
    bool __is_mine__() const override;
    bool is_seperable() const;
    int save() const override;
};

#endif // MINE_PLACE_H
