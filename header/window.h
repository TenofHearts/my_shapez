#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"
#include <QWidget>
#include <QFileDialog>
#include "gamescene.h"
#include "pausemenu.h"
#include "shopmenu.h"

/*
 * 开始界面，一次调用只有一个实例Global::w
 */

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void startGame();

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
