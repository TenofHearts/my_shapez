#include <global.h>
#include <mine.h>
#include <gamescene.h>

int Global::coin_num = 0;
int Global::hub_std = SMALL_HUB;
int Global::grid_std = 0;
int Global::ore_price = LOW_PRICE;
int Global::conveyor_speed = SLOW_BELT_SPEED;
int Global::miner_speed = SLOW_PRODUCE_TIME;
int Global::cutter_speed = SLOW_PRODUCE_TIME;

int Global::conveyor_upgrade = 0;
int Global::miner_upgrade = 0;
int Global::cutter_upgrade = 0;
int Global::grid_upgrade = 0;

QList<Mine *> Global::all_mine_vec;

QVector<Square *> Global::map(NUM_OF_HORIZONTAL_GRIDS * NUM_OF_VERTICAL_GRIDS);

// int Global::init_map[240] = {0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                              0, 0,  0,  15, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0,
//                              0, 0,  15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0,
//                              0, 0,  15, 15, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0,
//                              0, 15, 15, 15, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                              0, 0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 这是矿多的初始地图
int Global::init_map[240] = {0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, HUB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  24, 0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  24, 24, 0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

QString Global::dest[NUM_OF_MACHINES] = {ERASER_DEST, MINER_DEST, TRASHCAN_DEST, CUTTER_DEST, ROTATER_DEST, MERGER_DEST, SMALL_HUB_DEST, BIG_HUB_DEST};
QString Global::b_dest[NUM_OF_MACHINES] = {ERASER_DEST, MINER_B_DEST, TRASHCAN_B_DEST, CUTTER_B_DEST, ROTATER_B_DEST, MERGER_B_DEST, BELT_STRAIGHT_B, BELT_STRAIGHT_B};
QString Global::mine_place_dest[2] = {ROUND_MINE_DEST, SQUARE_MINE_DEST};
QString Global::ore_dest[4] = {ROUND_ORE_DEST, SQUARE_ORE_DEST, LEFT_ROUND_DEST, RIGHT_ROUND_DEST};
QString Global::belt_dest[3] = {BELT_LEFT, BELT_STRAIGHT, BELT_RIGHT};
QString Global::b_belt_dest[3] = {BELT_LEFT_B, BELT_STRAIGHT_B, BELT_RIGHT_B};

int Global::produce_time[2] = {SLOW_PRODUCE_TIME, FAST_PRODUCE_TIME};
int Global::belt_speed[2] = {SLOW_BELT_SPEED, FAST_BELT_SPEED};

QString Global::grid_dest[2] = {FEW_GRID_DEST, MANY_GRID_DEST};

Window *Global::w = nullptr;
GameScene *Global::game = nullptr;
PauseMenu *Global::pause = nullptr;
ShopMenu *Global::shop = nullptr;

QMediaPlayer *Global::player = nullptr;
QAudioOutput *Global::audio = nullptr;
int Global::volumn = 30;

QVector<int> Level::goal(4);
QVector<int> Level::cur(4);

int Global::getIndex(int x, int y)
{
    /*通过地块左上角x, y值来计算index*/
    return x / EDGE_LEN + (y - INIT_Y) / EDGE_LEN * NUM_OF_HORIZONTAL_GRIDS;
}

int Global::getXFromIndex(int index)
{
    /*通过地块index计算左上角x值*/
    return index % NUM_OF_HORIZONTAL_GRIDS * EDGE_LEN + INIT_X;
}

int Global::getYFromIndex(int index)
{
    /*通过地块index计算左上角y值*/
    return index / NUM_OF_HORIZONTAL_GRIDS * EDGE_LEN + INIT_Y;
}

int Global::getIndexinDirection(int index, int direction)
{
    /*获得index地块direction方向的地块index值*/
    if (direction % 2)
    {
        index += (direction - 2) * NUM_OF_HORIZONTAL_GRIDS;
    }
    else
    {
        index += direction - 1;
    }
    return index;
}

QString Global::display_coin()
{
    /*返回金币label应该显示的内容*/
    return QString("Cash:  %1 $").arg(coin_num);
}

bool Global::CheckJam(int index, int next_index, const Mine &ore_last)
{
    /*检查机器是否能输出，即输出的位置是否有尚未运走的矿*/
    int i = ore_last.get_index();
    bool res = (index == i) || (next_index == i);
    return res;
}

QString Global::display_progress(int type)
{
    /*返回type类矿物的收集情况，格式为：已收集/未收集*/
    return QString("%1/%2").arg(Level::cur[type]).arg(Level::goal[type]);
}

void Level::StartLevel()
{
    /*随机初始化一关的目标*/
    Global::miner_speed = SLOW_PRODUCE_TIME;
    Global::cutter_speed = SLOW_PRODUCE_TIME;
    Global::conveyor_speed = SLOW_BELT_SPEED;
    Global::miner_upgrade = false;
    Global::cutter_upgrade = false;
    Global::conveyor_upgrade = false;

    int ore_type = 0;
    srand(QTime::currentTime().msec());
    ore_type = rand() % 14 + 1;
    for (int i = 0; i < 4; ++i) {
        if ((ore_type >> i) & 1)
        {
            Level::goal[i] = (rand() % 4 + 1) * 10;
        }
        Level::cur[i] = 0;
    }
}

void Level::CheckVictory()
{
    /*检查是否胜利*/
    for (int i = 0; i < 4; ++i) {
        if (Level::cur[i] < Level::goal[i])
        {
            return;
        }
    }
    QMessageBox victory(Global::game);
    victory.setIconPixmap(QPixmap(VICTORY_ICON));
    victory.setText("恭喜你！通关了！");
    victory.setWindowTitle("Congratulations!!");
    victory.exec();
    StartLevel();

    if (Global::game && Global::shop)
    {
        Global::shop->setGeometry(Global::game->geometry());
        Global::shop->show();
        Global::game->hide();
    }
}

void Global::reset_map()
{
    /*当存档受损时，开始新游戏*/
    int map[240] = {0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 6,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  24, 0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  24, 24, 0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0,  0,  0,  0,  0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 240; ++i)
    {
        Global::init_map[i] = map[i];
        if (Global::map[i])
        {
            delete Global::map[i];
            Global::map[i] = nullptr;
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        Level::goal[i] = 0;
        Level::cur[i] = 0;
    }
    Global::coin_num = 0;
    Global::hub_std = SMALL_HUB;
    Global::grid_std = 0;
    Global::ore_price = LOW_PRICE;
    Global::conveyor_speed = SLOW_BELT_SPEED;
    Global::miner_speed = SLOW_PRODUCE_TIME;
    Global::cutter_speed = SLOW_PRODUCE_TIME;

    Global::conveyor_upgrade = 0;
    Global::miner_upgrade = 0;
    Global::cutter_upgrade = 0;
    Global::grid_upgrade = 0;
}