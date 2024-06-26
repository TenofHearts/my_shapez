#ifndef SHOPMENU_H
#define SHOPMENU_H

#include <QWidget>
#include <global.h>

/*
 * 此类为商店界面，一次运行时只会有一个实例Global::shop
 */

namespace Ui {
class ShopMenu;
}

class ShopMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ShopMenu(QWidget *parent = nullptr);
    ~ShopMenu();
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;

private:
    Ui::ShopMenu *ui;
};

#endif // SHOPMENU_H
