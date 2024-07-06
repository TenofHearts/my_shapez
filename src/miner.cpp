#include "miner.h"
#include "gamescene.h"
#include "mine.h"

Miner::Miner(int x, int y, int direction, int type, QWidget *parent):
    Machine(x, y, direction, parent), type(type)
{
    Miner::connect(this, &Miner::erase, [=](){
        int index = Global::getIndex(x, y);
        if (Global::map[index] && Global::map[index]->__is_machine__())
        {
            delete Global::map[index];
            Global::map[index] = new Mine_Place(X(), Y(), get_type(), parent);
        }
    });

    void (Miner::*func)(void) = &Miner::function;
    connect(Global::game->game_engine[0], &QTimer::timeout, this, func);
}

Miner::~Miner()
{}

void placeMiner()
{
    QTimer *timer = new QTimer;
    timer->start(40);
    GameScene::connect(timer, &QTimer::timeout, [=]()
    {
        Global::game->update();
    });

    Device::inLoop = true;
    Device::placeMachine = false;
    Device::typeofMachine = MINER;
    while (Device::inLoop)
    {
        Global::game->setMouseTracking(true);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
    }
    if (Device::placeMachine)
    {
        int index = Global::getIndex(Global::game->get_mouse_x(), Global::game->get_mouse_y());
        Square *temp = new Miner(Global::getXFromIndex(index), Global::getYFromIndex(index), Device::direction, static_cast<Mine_Place *>(Global::map[index])->get_type(), Global::game);

        Square *t = temp;
        temp = Global::map[index];
        Global::map[index] = t;

        if (temp) delete temp;
    }
    delete timer;
    Device::placeMachine = false;
    Device::typeofMachine = 0;
}

void Miner::show(QPainter &painter) const
{
    QPixmap miner(Global::dest[MINER]);


    QTransform transform;
    transform.rotate(90 * get_direction());

    painter.drawPixmap(X(), Y(), EDGE_LEN, EDGE_LEN, miner.transformed(transform));
}

short Miner::get_type() const
{
    return type;
}

void Miner::function()
{
    int offset = EDGE_LEN / 2 - Global::conveyor_speed;
    int dir = (get_direction() + 2) % 4;
    int next_index = Global::getIndexinDirection(get_index(), get_direction());
    int delta_x = (1 - (dir & 1)) * (dir >> 1 ? 1 : -1) * offset;
    int delta_y = (dir & 1) * (dir >> 1 ? 1 : -1) * offset;
    if (Global::map[next_index] && Global::map[next_index]->__is_machine__() && static_cast<Machine *>(Global::map[next_index])->can_enter(get_index()))
    {
        Mine *temp = new Mine(Global::getXFromIndex(next_index) + delta_x, Global::getYFromIndex(next_index) + delta_y, get_type(), Global::game);
        Global::all_mine_vec.push_back(temp);

        Abrasion();
    }
}

int Miner::save() const
{
    return MINER | (get_direction() << TYPE_DIGITS) | (type << (TYPE_DIGITS + DIRECTION_DIGITS));
}

int Miner::function(Mine &ore)
{
    int delta_x = (1 - (get_direction() & 1)) * ((get_direction() >> 1) ? 1 : -1) * Global::conveyor_speed;
    ore.getx() += delta_x;
    int delta_y = (get_direction() & 1) * ((get_direction() >> 1) ? 1 : -1) * Global::conveyor_speed;
    ore.gety() += delta_y;

    return 0;
}

bool Miner::can_enter(int) const
{
    return false;
}

void Miner::Abrasion() const
{
    if (Global::coin_num >= MACHINE_ABRASION_FEE * (Global::miner_upgrade + 1))
    {
        Global::coin_num -= MACHINE_ABRASION_FEE * (Global::miner_upgrade + 1);
    }
}