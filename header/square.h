#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include "global.h"

/*
 * 地图上所有地块的基类，维护了基本的接口
 */

class Square : public QWidget
{
    Q_OBJECT
    int x, y;
    bool coverable;

public:
    explicit Square(int x, int y, QWidget *parent = nullptr, bool coverable = true);
    explicit Square(int index, QWidget *parent = nullptr, bool coverable = true);
    virtual ~Square();
    int &getx();
    int &gety();
    int X() const;
    int Y() const;
    virtual void show(QPainter &) const;
    bool is_coverable() const;
    void __set_coverable__(bool c);
    virtual bool __is_mine__() const;
    virtual bool __is_machine__() const;
    void paintEvent(QPaintEvent *) override;
    virtual int save() const;
    virtual int get_index() const;
    void getCenter(int &x, int &y) const;


signals:
};



#endif // SQUARE_H
