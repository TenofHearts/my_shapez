#include "header/square.h"

Square::Square(int x, int y, QWidget *parent, bool coverable)
    : QWidget{parent}, x(x), y(y), coverable(coverable)
{}

Square::Square(int index, QWidget *parent, bool coverable)
    : QWidget{parent}, x(Global::getXFromIndex(index)), y(Global::getYFromIndex(index)), coverable(coverable)
{}

Square::~Square()
{}

int &Square::getx()
{
    /*获得该方格左上角x值的引用*/
    return x;
}

int &Square::gety()
{
    /*获得该方格左上角y值的引用*/
    return y;
}

int Square::X() const
{
    /*获得该方格左上角的x值*/
    return x;
}

int Square::Y() const
{
    /*获得该方格左上角的y值*/
    return y;
}

void Square::show(QPainter &) const
{
    /*显示该方格的内容*/
    // qDebug() << "Don't show in base class";
}

bool Square::is_coverable() const
{
    /*
     * 判断该方格上是否可以放置机器
     * 无用接口
     */
    return coverable;
}

void Square::__set_coverable__(bool c)
{
    /*
     * 将该方格的coverable参数设为c
     * 无用接口
     */
    coverable = c;
}

bool Square::__is_mine__() const
{
    /*返回该地块是否是采矿点*/
    // qDebug() << is_mine;
    return false;
}

bool Square::__is_machine__() const
{
    /*返回该地块是否是机器*/
    return false;
}

void Square::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    this->show(painter);
}

int Square::save() const
{
    /*
     * 存档时调用，将地块中的信息以二进制的方式存为一个整数
     *
     * 返回该整数
     */
    return 0;
}

int Square::get_index() const
{
    /*获得地块的index*/
    return Global::getIndex(X(), Y());
}

void Square::getCenter(int &x, int &y) const
{
    x = this->X() + EDGE_LEN / 2;
    y = this->Y() + EDGE_LEN / 2;
}