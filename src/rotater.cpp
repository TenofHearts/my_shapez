#include "rotater.h"
#include <gamescene.h>

Rotater::Rotater(int x, int y, int direction, QWidget *parent):
    Machine(x, y, direction, parent)
{
    connect(this, &Rotater::erase, [=](){
        int index = get_index();
        if (Global::map[index] && Global::map[index]->__is_machine__())
        {
            delete Global::map[index];
            Global::map[index] = nullptr;
        }
    });

    void (Rotater::*func)(void) = &Rotater::function;
    connect(Global::game->game_engine[2], &QTimer::timeout, this, func);
    to_produce = 0;
}

Rotater::~Rotater()
{}

void placeRotater()
{
    QTimer *timer = new QTimer;
    timer->start(40);
    GameScene::connect(timer, &QTimer::timeout, [=]()
                       {
                           Global::game->update();
                       });

    Device::inLoop = true;
    Device::placeMachine = false;
    Device::typeofMachine = ROTATER;
    while (Device::inLoop)
    {
        Global::game->setMouseTracking(true);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
    }
    if (Device::placeMachine)
    {
        int index = Global::getIndex(Global::game->get_mouse_x(), Global::game->get_mouse_y());
        Square *temp = new Rotater(Global::getXFromIndex(index), Global::getYFromIndex(index), Device::direction, Global::game);

        Square *t = temp;
        temp = Global::map[index];
        Global::map[index] = t;

        if (temp) delete temp;
    }
    delete timer;
    Device::placeMachine = false;
    Device::typeofMachine = 0;
}

void Rotater::show(QPainter &painter) const
{
    QTransform transform;
    transform.rotate(90 * get_direction());

    painter.drawPixmap(X(), Y(), EDGE_LEN, EDGE_LEN, QPixmap(ROTATER_DEST).transformed(transform));
}

void Rotater::function()
{
    if (to_produce)
    {
        int offset = EDGE_LEN / 2 - Global::conveyor_speed;
        int dir = (get_direction() + 2) % 4;
        int next_index = Global::getIndexinDirection(get_index(), get_direction());
        int delta_x = (1 - (dir & 1)) * (dir >> 1 ? 1 : -1) * offset;
        int delta_y = (dir & 1) * (dir >> 1 ? 1 : -1) * offset;
        if (Global::map[next_index] && Global::map[next_index]->__is_machine__() && static_cast<Machine *>(Global::map[next_index])->can_enter(get_index()))
        {
            int to_1 = 1 & (to_produce - 1), to_2 = (to_produce - 1) >> 1;
            int type = to_2 << 1 | (to_1 ^ to_2);
            Mine *temp = new Mine(Global::getXFromIndex(next_index) + delta_x, Global::getYFromIndex(next_index) + delta_y, type, Global::game);
            Global::all_mine_vec.push_back(temp);

            to_produce = 0;

            Abrasion();
        }
    }
}

int Rotater::function(Mine &ore)
{
    int x, y;
    ore.getCenter(x, y);
    int x_, y_;
    this->getCenter(x_, y_);
    int delta_x = (x_ - x) / 13, delta_y = (y_ - y) / 13;
    if (-delta_x - delta_y + abs(delta_x) + 2 * abs(delta_y) == get_direction())
    {
        int d_x = (1 - (get_direction() & 1)) * ((get_direction() >> 1) ? 1 : -1) * Global::conveyor_speed;
        ore.getx() += d_x;
        int d_y = (get_direction() & 1) * ((get_direction() >> 1) ? 1 : -1) * Global::conveyor_speed;
        ore.gety() += d_y;

        return 0;
    }
    else
    {
        to_produce = ore.get_type() + 1;

        return 1;
    }
    return 0;
}

int Rotater::save() const
{
    return ROTATER | (get_direction() << TYPE_DIGITS);
}

bool Rotater::can_enter(int index) const
{
    return to_produce == 0 && index == get_enter_index();
}

void Rotater::Abrasion() const
{
    if (Global::coin_num >= MACHINE_ABRASION_FEE)
    {
        Global::coin_num -= MACHINE_ABRASION_FEE;
    }
}