#ifndef GLOBAL_H
#define GLOBAL_H

#include <QVector>
#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QMouseEvent>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMessageBox>
#include <QtGlobal>
#include <QTime>

class Mine;
class Square;
class Window;
class GameScene;
class PauseMenu;
class ShopMenu;

#define EDGE_LEN 40
#define NUM_OF_HORIZONTAL_GRIDS 20
#define NUM_OF_VERTICAL_GRIDS 12
#define INIT_X 0
#define INIT_Y 40
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define LEFT 0
#define UP 1
#define DOWN 3
#define RIGHT 2

#define BACKGROUND_DEST ":/res/background.jpg"
#define ICON_DEST ":/res/icon.png"
#define FEW_GRID_DEST ":/res/grid.jpg"
#define MANY_GRID_DEST ":/res/grid_1.jpg"
#define MINER_B_DEST ":/res/miner_blue.png"
#define MINER_DEST ":/res/miner.png"
#define TRASHCAN_B_DEST ":/res/trash_blue.png"
#define TRASHCAN_DEST ":/res/trash.png"
#define CUTTER_DEST ":/res/cutter.png"
#define CUTTER_B_DEST ":/res/cutter_blue.png"
#define ROUND_MINE_DEST ":/res/cycle_mine.png"
#define SQUARE_MINE_DEST ":/res/rect_mine.png"
#define LEFT_ROUND_DEST ":/res/left_cycle.png"
#define RIGHT_ROUND_DEST ":/res/right_cycle.png"
#define ROUND_ORE_DEST ":/res/cycle.png"
#define SQUARE_ORE_DEST ":/res/rect.png"
#define ERASER_DEST ":/res/eraser.png"
#define SMALL_HUB_DEST ":/res/hub_small.png"
#define BIG_HUB_DEST ":/res/hub_big.png"
#define ROTATER_DEST ":/res/rotater.png"
#define ROTATER_B_DEST ":/res/rotater_blue.png"
#define BELT_STRAIGHT ":/res/belt.png"
#define BELT_LEFT ":/res/belt_left.png"
#define BELT_RIGHT ":/res/belt_right.png"
#define BELT_STRAIGHT_B ":/res/belt_blue.png"
#define BELT_LEFT_B ":/res/belt_blue_left.png"
#define BELT_RIGHT_B ":/res/belt_blue_right.png"
#define VICTORY_ICON ":/res/win.png"
#define MERGER_B_DEST ":/res/merger_blue.png"
#define MERGER_DEST ":/res/merger.png"
#define BGM_DEST "qrc:/res/You're_Beautiful.mp3"

#define MINER 1
#define TRASHCAN 2
#define CUTTER 3
#define HUB 6
#define CONVEYOR 7
#define ROTATER 4
#define MINING_PLACE 8
#define MERGER 5
#define NUM_OF_MACHINES 8

#define TURN_LEFT 0
#define TURN_STRAIGHT 1
#define TURN_RIGHT 2

#define ROUND 0
#define SQUARE 1
#define LEFT_HALF 2
#define RIGHT_HALF 3
#define DELETE -1

#define SLOW_PRODUCE_TIME 3000
#define FAST_PRODUCE_TIME 2000

#define SLOW_BELT_SPEED 2
#define FAST_BELT_SPEED 4

#define SLOW 0
#define FAST 1

#define TYPE_DIGITS 4
#define TYPE_BITS 0b1111
#define DIRECTION_DIGITS 2
#define DIRECTION_BITS 0b11
#define ORE_TYPE_DIGITS 2
#define ORE_TYPE_BITS 0b11

#define TEMP_PRICE 100
#define PERMANENT_PRICE 500

#define HUB_INDEX 48
#define SMALL_HUB 1
#define BIG_HUB 2

#define LOW_PRICE 10
#define HIGH_PRICE 25

#define MACHINE_ABRASION_FEE 2

namespace Global
{
    extern int coin_num;
    extern int hub_std;
    extern int grid_std;
    extern int ore_price;
    extern int conveyor_speed;
    extern int miner_speed;
    extern int cutter_speed;

    extern int conveyor_upgrade;
    extern int miner_upgrade;
    extern int cutter_upgrade;
    extern int grid_upgrade;

    extern int init_map[240];

    extern QList<Mine *> all_mine_vec;
    extern QVector<Square *> map;

    extern QString dest[NUM_OF_MACHINES];
    extern QString b_dest[NUM_OF_MACHINES];
    extern QString mine_place_dest[2];
    extern QString ore_dest[4];
    extern QString belt_dest[3];
    extern QString b_belt_dest[3];
    extern QString grid_dest[2];

    extern Window *w;
    extern GameScene *game;
    extern PauseMenu *pause;
    extern ShopMenu *shop;

    extern int produce_time[2];
    extern int belt_speed[2];

    int getIndex(int x, int y);
    int getXFromIndex(int index);
    int getYFromIndex(int index);
    int getIndexinDirection(int index, int direction);
    QString display_coin();
    bool CheckJam(int index, int next_index, const Mine &ore_last);
    QString display_progress(int type);
    void reset_map();

    extern QMediaPlayer *player;
    extern QAudioOutput *audio;
    extern int volumn;

}

namespace Level
{
    extern QVector<int> goal;
    extern QVector<int> cur;

    void StartLevel();
    void CheckVictory();
}

#endif // GLOBAL_H
