#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include "global.h"
#include "shopmenu.h"
#include "square.h"
#include "machine.h"
#include "cutter.h"
#include "miner.h"
#include "trashcan.h"
#include "mine_place.h"
#include "conveyor.h"
#include "mine.h"
#include "pausemenu.h"
#include "hub.h"

/*
 * 游戏界面，一次运行中只会有一个实例Global::game
 */

namespace Ui {
class GameScene;
}

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);
    ~GameScene();
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void keyPressEvent(QKeyEvent *ev) override;
    int get_mouse_x();
    int get_mouse_y();
    void hideEvent(QHideEvent *ev) override;
    void showEvent(QShowEvent *ev) override;
    void LoadMap();
    void upgrade_map();
private:
    Ui::GameScene *ui;

private:
    int mouse_x, mouse_y;

public:
    QTimer *animation_timer, *game_engine[3];
};

bool Conditions(int);

#endif // GAMESCENE_H
