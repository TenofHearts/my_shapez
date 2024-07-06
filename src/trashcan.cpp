#include "header/trashcan.h"
#include "header/gamescene.h"
#include "header/mine.h"

Trashcan::Trashcan(int x, int y, QWidget *parent):
    Machine(x, y, LEFT, parent)
{
    Trashcan::connect(this, &Trashcan::erase, [=](){
        int index = Global::getIndex(x, y);
        if (Global::map[index])
        {
            delete Global::map[index];
            Global::map[index] = nullptr;
        }
    });
}

Trashcan::~Trashcan()
{}

void Trashcan::show(QPainter &painter) const
{
    painter.drawPixmap(X(), Y(), EDGE_LEN, EDGE_LEN, QPixmap(TRASHCAN_DEST));
}

void placeTrashcan()
{
    QTimer *timer = new QTimer;
    timer->start(40);
    GameScene::connect(timer, &QTimer::timeout, [=]()
                       {
                           Global::game->update();
                       });

    Device::inLoop = true;
    Device::placeMachine = false;
    Device::typeofMachine = TRASHCAN;
    while (Device::inLoop)
    {
        Global::game->setMouseTracking(true);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
    }
    if (Device::placeMachine)
    {
        int index = Global::getIndex(Global::game->get_mouse_x(), Global::game->get_mouse_y());
        if (Global::map[index])
        {
            delete Global::map[index];
        }
        Global::map[index] = new Trashcan(Global::getXFromIndex(index), Global::getYFromIndex(index), Global::game);
    }
    delete timer;
    Device::placeMachine = false;
    Device::typeofMachine = 0;
}

int Trashcan::function(Mine &)
{
    Abrasion();
    return 1;
}

int Trashcan::save() const
{
    return TRASHCAN;
}

bool Trashcan::can_enter(int) const
{
    return true;
}

void Trashcan::Abrasion() const
{
    if (Global::coin_num >= MACHINE_ABRASION_FEE)
    {
        Global::coin_num -= MACHINE_ABRASION_FEE;
    }
}