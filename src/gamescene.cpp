#include "gamescene.h"
#include "ui_gamescene.h"
#include <mine_place.h>
#include <rotater.h>
#include <merger.h>

static QVector<int> round_upgrade_list {97, 117, 136, 137, 138, 158, 177};
static QVector<int> rect_upgrade_list {102, 103, 104, 122, 123, 141};

static bool canPlace = false;

GameScene::GameScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScene)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(ICON_DEST));
    setWindowTitle("shapez");
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);

    // setMouseTracking(true);

    animation_timer = new QTimer(this);
    game_engine[0] = new QTimer(this);
    game_engine[1] = new QTimer(this);
    game_engine[2] = new QTimer(this);

    connect(animation_timer, &QTimer::timeout, [=](){
        update();
        action(Global::all_mine_vec);

        ui->coin_count_label->setText(Global::display_coin());
        ui->round_ore_label_t->setText(Global::display_progress(ROUND));
        ui->rect_ore_label_t->setText(Global::display_progress(SQUARE));
        ui->left_half_label_t->setText(Global::display_progress(LEFT_HALF));
        ui->right_half_label_t->setText(Global::display_progress(RIGHT_HALF));

        Level::CheckVictory();
    });

    connect(ui->miner_btn, &QToolButton::clicked, [=](){placeMiner();});

    connect(ui->transhcan_btn, &QToolButton::clicked, [=](){placeTrashcan();});

    connect(ui->cutter_btn, &QToolButton::clicked, [=](){placeCutter();});

    connect(ui->conveyor_btn, &QToolButton::clicked, [=](){placeConveyer();});

    connect(ui->rotater_btn, &QToolButton::clicked, [=](){placeRotater();});

    connect(ui->merger_btn, &QToolButton::clicked, [=](){placeMerger();});

    connect(ui->eraser_btn, &QToolButton::clicked, [=](){
        Device::direction = LEFT;
        Device::inLoop = true;
        while (Device::inLoop)
        {
            setMouseTracking(true);
            QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
        }
        int index = Global::getIndex(mouse_x, mouse_y);
        if (Global::map[index] && Global::map[index]->__is_machine__())
        {
            emit static_cast<Machine *>(Global::map[index])->erase();
        }
        setMouseTracking(false);

    });

    connect(ui->help_btn, &QToolButton::clicked, [=](){
        Global::pause->setGeometry(this->geometry());
        Global::pause->show();
        this->hide();
    });

    connect(ui->shop_btn, &QToolButton::clicked, [=](){
        Global::shop->setGeometry(this->geometry());
        Global::shop->show();
        this->hide();
    });

    ui->round_ore_label->setScaledContents(true);
    ui->round_ore_label->setPixmap(QPixmap(ROUND_ORE_DEST));
    ui->rect_ore_label->setScaledContents(true);
    ui->rect_ore_label->setPixmap(QPixmap(SQUARE_ORE_DEST));
    ui->left_half_label->setScaledContents(true);
    ui->left_half_label->setPixmap(QPixmap(LEFT_ROUND_DEST));
    ui->right_half_label->setScaledContents(true);
    ui->right_half_label->setPixmap(QPixmap(RIGHT_ROUND_DEST));
}

void GameScene::LoadMap()
{
    /*
     * 加载存档中的内容
     * 后三位代表种类，之后每两位代表一个特征
     * 在创建Global::game后自动调用
     */
    for (int i = 0; i < 240; i++)
    {
        if (Global::map[i])
        {
            continue;
        }
        int sqr = Global::init_map[i];
        switch (sqr & TYPE_BITS) {
        case 0:
            break;
        case MINING_PLACE:
            if (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS)) throw -1;
            Global::map[i] = new Mine_Place(Global::getXFromIndex(i), Global::getYFromIndex(i), (sqr >> TYPE_DIGITS) & DIRECTION_BITS, this);
            break;
        case MINER:
            if (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS + ORE_TYPE_DIGITS)) throw -1;
            Global::map[i] = new Miner(Global::getXFromIndex(i), Global::getYFromIndex(i), (sqr >> TYPE_DIGITS) & DIRECTION_BITS, (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS)) & ORE_TYPE_BITS, this);
            break;
        case CONVEYOR:
            Global::map[i] = new Conveyor(Global::getXFromIndex(i), Global::getYFromIndex(i), (sqr >> TYPE_DIGITS) & DIRECTION_BITS, (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS) & DIRECTION_BITS), this);
            if (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS * 2)) throw -1;
            break;
        case CUTTER:
            if (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS)) throw -1;
            Global::map[i] = new Cutter(Global::getXFromIndex(i), Global::getYFromIndex(i), (sqr >> TYPE_DIGITS) & DIRECTION_BITS, this);
            break;
        case TRASHCAN:
            if (sqr >> (TYPE_DIGITS)) throw -1;
            Global::map[i] = new Trashcan(Global::getXFromIndex(i), Global::getYFromIndex(i), this);
            break;
        case HUB:
            if (sqr != HUB || i != HUB_INDEX) throw -1;
            Global::map[i] = new Hub(i, this);
            break;
        case ROTATER:
            if (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS)) throw -1;
            Global::map[i] = new Rotater(Global::getXFromIndex(i), Global::getYFromIndex(i), (sqr >> TYPE_DIGITS) & DIRECTION_BITS, this);
            break;
        case MERGER:
            if (sqr >> (TYPE_DIGITS + DIRECTION_DIGITS)) throw -1;
            Global::map[i] = new Merger(Global::getXFromIndex(i), Global::getYFromIndex(i), (sqr >> TYPE_DIGITS) & DIRECTION_BITS, this);
            break;
        default:
            throw -1;
            break;
        }
    }
    if (!(Level::goal[ROUND] || Level::goal[SQUARE] || Level::goal[LEFT_HALF] || Level::goal[RIGHT_HALF]))
    {
        Level::StartLevel();
    }
}

GameScene::~GameScene()
{
    delete ui;
    delete game_engine[0];
    delete game_engine[1];
    delete game_engine[2];
    delete animation_timer;
}

void GameScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap background(Global::grid_dest[Global::grid_std]);

    painter.drawPixmap(this->rect(), background);

    /*************************/

    for(auto &&sqr: Global::map)
    {
        if (sqr)
        {
            sqr->show(painter);
        }
    }

    /*************************/

    for (auto &&ore: Global::all_mine_vec)
    {
        ore->show(painter);
    }

    /*************************/

    if (Device::inLoop && !Belt::placing_belt)
    {
        int x, y;

        QPixmap pic(Global::b_dest[Device::typeofMachine]);

        QTransform transformer;

        if (canPlace)
        {
            x = Global::getXFromIndex(Global::getIndex(mouse_x, mouse_y));
            y = Global::getYFromIndex(Global::getIndex(mouse_x, mouse_y));
        }
        else
        {
            x = mouse_x - EDGE_LEN / 2;
            y = mouse_y - EDGE_LEN / 2;
        }

        transformer.translate(x, y);
        transformer.rotate(Device::direction * 90);
        transformer.translate( -EDGE_LEN * (Device::direction >> 1), -EDGE_LEN * ((Device::direction & 1) ^ (Device::direction >> 1))); // 这是通过计算和分析得到的结果

        painter.setTransform(transformer, true);

        if (Device::typeofMachine != CUTTER) {painter.drawPixmap(0, 0, EDGE_LEN, EDGE_LEN, pic);}
        else {painter.drawPixmap(0, 0, EDGE_LEN, EDGE_LEN * 2, pic);}

        painter.setTransform(transformer, false);
    }

    /***************************/

    if (Belt::placing_belt)
    {
        QTransform transformer;

        if (Belt::virtual_index.size() > 1)
        {
            short last_direction = getDirectionFromIndices(Belt::virtual_index[0], Belt::virtual_index[1]);

            transformer.rotate((last_direction + 2) % 4 * 90);
            painter.drawPixmap(Global::getXFromIndex(Belt::virtual_index[0]), Global::getYFromIndex(Belt::virtual_index[0]), EDGE_LEN, EDGE_LEN, QPixmap(Global::b_belt_dest[TURN_STRAIGHT]).transformed(transformer));

            for (int i = 1; i < Belt::virtual_index.size() - 1; ++i)
            {
                short current_direction = getDirectionFromIndices(Belt::virtual_index[i], Belt::virtual_index[i + 1]);
                transformer.reset();
                transformer.rotate((last_direction + 2) % 4 * 90);
                painter.drawPixmap(Global::getXFromIndex(Belt::virtual_index[i]), Global::getYFromIndex(Belt::virtual_index[i]), EDGE_LEN, EDGE_LEN, QPixmap(Global::b_belt_dest[getTurnDirection(last_direction, current_direction)]).transformed(transformer));
                last_direction = current_direction;
            }

            transformer.reset();
            transformer.rotate((last_direction + 2) % 4 * 90);
            painter.drawPixmap(Global::getXFromIndex(Belt::virtual_index.last()), Global::getYFromIndex(Belt::virtual_index.last()), EDGE_LEN, EDGE_LEN, QPixmap(Global::b_belt_dest[TURN_STRAIGHT]).transformed(transformer));
        }
    }
}

void GameScene::mousePressEvent(QMouseEvent *ev)
{
    /*处理放置机器的事件*/
    // QString str = QString("第%1格").arg(ev->pos().x() / EDGE_LEN + (ev->pos().y() - INIT_Y) / EDGE_LEN * NUM_OF_HORIZONTAL_GRIDS);
    // qDebug() << str.toUtf8().data();
    if (Device::inLoop && ev->button() == Qt::RightButton)
    {
        Device::inLoop = false;
        setMouseTracking(false);
    }
    else if (Device::inLoop && ev->button() == Qt::LeftButton)
    {
        if (canPlace)
        {
            Device::inLoop = false;
            Device::placeMachine = true;
            setMouseTracking(false);
            canPlace = false;
        }

        if (Device::typeofMachine == CONVEYOR && !Belt::placing_belt)
        {
            Belt::placing_belt = true;
            canPlace = false;
        }
    }
    else if (ev->button() == Qt::RightButton)
    {
        int index = Global::getIndex(ev->pos().x(), ev->pos().y());
        if (Global::map[index] && Global::map[index]->__is_machine__())
        {
            emit static_cast<Machine *>(Global::map[index])->erase();
        }
    }
}

void GameScene::mouseMoveEvent(QMouseEvent *ev)
{
    /*处理放置机器*/
    mouse_x = ev->pos().x();
    mouse_y = ev->pos().y();
    canPlace = Conditions(Global::getIndex(mouse_x, mouse_y));

    /*处理放置传送带时的动态*/
    if (Belt::placing_belt)
    {
        int index = Global::getIndex(mouse_x, mouse_y);
        auto iter = Belt::virtual_index.begin();
        for (; iter != Belt::virtual_index.end(); iter++)
        {
            if (*iter == index)
            {
                break;
            }
        }
        Belt::virtual_index.erase(iter, Belt::virtual_index.end());
        if (Belt::virtual_index.isEmpty() || (index != Belt::virtual_index.last() && (index == Belt::virtual_index.last() - 1 || index == Belt::virtual_index.last() + 1 || index == Belt::virtual_index.last() - 20 || index == Belt::virtual_index.last() + 20)))
        {
            Belt::virtual_index.push_back(index);
        }
    }
}

void GameScene::keyPressEvent(QKeyEvent *ev)
{
    /*改变放置机器的方向*/
    if (ev->key() == Qt::Key_R)
    {
        (++Device::direction) %= 4;
    }
}

int GameScene::get_mouse_x()
{
    return mouse_x;
}

int GameScene::get_mouse_y()
{
    return mouse_y;
}

bool Conditions(int index)
{
    /*分种类处理某种机器是否能够放在index地块*/
    int sub_dir = (Device::direction + 3) % 4;
    int sub_index = Global::getIndexinDirection(index, sub_dir);
    if (index  < 0 || index > 239)
    {
        return false;
    }

    switch (Device::typeofMachine) {
    case MINER:
        return Global::map[index] && Global::map[index]->__is_mine__() && Global::map[index]->is_coverable();
    case TRASHCAN:
        return Global::map[index] == nullptr || (!Global::map[index]->__is_mine__() && Global::map[index]->is_coverable());
    case CUTTER:
        if (sub_index >= 0 && sub_index <= 239)
        {
            return Global::map[index] == nullptr && Global::map[sub_index] == nullptr;
        }
        else
        {
            return false;
        }
    case ROTATER:
        return Global::map[index] == nullptr;
    case 0:
        return Global::map[index] && Global::map[index]->__is_machine__();
    case CONVEYOR:
        return Belt::placing_belt;
    case MERGER:
        return Global::map[index] == nullptr;
    default:
        return false;
    }
}

void GameScene::hideEvent(QHideEvent *ev)
{
    /*调用hide()槽函数时自动调用*/
    QWidget::hideEvent(ev);

    animation_timer->stop();
    game_engine[0]->stop();
    game_engine[1]->stop();
    game_engine[2]->stop();

}

void GameScene::showEvent(QShowEvent *ev)
{
    /*调用show()槽函数时自动调用*/
    QWidget::showEvent(ev);

    animation_timer->start(40);
    game_engine[0]->start(Global::miner_speed);
    game_engine[1]->start(Global::cutter_speed);
    game_engine[2]->start(1000);

    emit static_cast<Hub *>(Global::map[HUB_INDEX])->check_upgrade();
    if (Global::grid_upgrade != Global::grid_std)
    {
        upgrade_map();
    }
}

void GameScene::upgrade_map()
{
    Global::grid_std = Global::grid_upgrade;
    for (auto &&i: round_upgrade_list)
    {
        if (Global::map[i] && Global::map[i]->__is_machine__())
        {
            emit static_cast<Machine *>(Global::map[i])->erase();
        }
        Global::map[i] = new Mine_Place(i, ROUND, this);
    }
    for (auto &&i: rect_upgrade_list)
    {
        if (Global::map[i] && Global::map[i]->__is_machine__())
        {
            emit static_cast<Machine *>(Global::map[i])->erase();
        }
        Global::map[i] = new Mine_Place(i, SQUARE, this);
    }
}