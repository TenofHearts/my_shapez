#include "merger.h"
#include <gamescene.h>

Merger::Merger(int x, int y, int direction, QWidget *parent):
    Machine(x, y, direction, parent)
{
    from_bottom = 1;
    to_produce = -1;

    void (Merger::*func)(void) = &Merger::function;
    connect(Global::game->game_engine[2], &QTimer::timeout, this, func);

    connect(this, &Merger::erase, [=](){
        int index = get_index();
        if (Global::map[index] && Global::map[index]->__is_machine__())
        {
            delete Global::map[index];
            Global::map[index] = nullptr;
        }
    });
}

Merger::~Merger()
{}

void placeMerger()
{
    QTimer *timer = new QTimer;
    timer->start(40);
    GameScene::connect(timer, &QTimer::timeout, [=]()
                       {
                           Global::game->update();
                       });

    Device::inLoop = true;
    Device::placeMachine = false;
    Device::typeofMachine = MERGER;
    while (Device::inLoop)
    {
        Global::game->setMouseTracking(true);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
    }
    if (Device::placeMachine)
    {
        int index = Global::getIndex(Global::game->get_mouse_x(), Global::game->get_mouse_y());
        Square *temp = new Merger(Global::getXFromIndex(index), Global::getYFromIndex(index), Device::direction, Global::game);

        Square *t = temp;
        temp = Global::map[index];
        Global::map[index] = t;

        if (temp) delete temp;
    }
    delete timer;
    Device::placeMachine = false;
    Device::typeofMachine = 0;
}

void Merger::show(QPainter &painter) const
{
    QTransform transform;
    transform.rotate(90 * get_direction());

    painter.drawPixmap(X(), Y(), EDGE_LEN, EDGE_LEN, QPixmap(MERGER_DEST).transformed(transform));
}

int Merger::save() const
{
    return MERGER | (get_direction() << TYPE_DIGITS);
}

bool Merger::can_enter(int index) const
{
    if (to_produce == -1)
    {
        if (from_bottom)
        {
            return index == Global::getIndexinDirection(get_index(), (get_direction() + 2) % 4);
        }
        else
        {
            return index == Global::getIndexinDirection(get_index(), (get_direction() + 1) % 4);
        }
    }
    else
    {
        return false;
    }
}

void Merger::function()
{
    if (to_produce >= 0)
    {
        int offset = EDGE_LEN / 2 - Global::conveyor_speed;
        int dir = (get_direction() + 2) % 4;
        int next_index = Global::getIndexinDirection(get_index(), get_direction());
        int delta_x = (1 - (dir & 1)) * (dir >> 1 ? 1 : -1) * offset;
        int delta_y = (dir & 1) * (dir >> 1 ? 1 : -1) * offset;
        if (Global::map[next_index] && Global::map[next_index]->__is_machine__() && static_cast<Machine *>(Global::map[next_index])->can_enter(get_index()))
        {
            Mine *temp = new Mine(Global::getXFromIndex(next_index) + delta_x, Global::getYFromIndex(next_index) + delta_y, to_produce, Global::game);
            Global::all_mine_vec.push_back(temp);

            to_produce = -1;
            from_bottom = !from_bottom;

            Abrasion();
        }
    }
}

void Merger::Abrasion() const
{
    if (Global::coin_num >= MACHINE_ABRASION_FEE)
    {
        Global::coin_num -= MACHINE_ABRASION_FEE;
    }
}

int Merger::function(Mine &ore)
{
    to_produce = ore.get_type();

    return 1;
}