#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <global.h>

/*
 * 此类为暂停界面的设计，在一次调用中只有一个实例Global::pause
 */

namespace Ui {
class PauseMenu;
}

class PauseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PauseMenu(QWidget *parent = nullptr);
    ~PauseMenu();
    void paintEvent(QPaintEvent *) override;

private:
    Ui::PauseMenu *ui;
};

#endif // PAUSEMENU_H
