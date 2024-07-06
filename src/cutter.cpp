#include "cutter.h"
#include "gamescene.h"

Cutter::Cutter(int x, int y, int direction, QWidget *parent):
    Machine(x, y, direction, parent)
{
    int sub_direction = (direction + 3) % 4;
    int index = Global::getIndex(x, y);
    int sub_index = Global::getIndexinDirection(index, sub_direction);
    sub_cutter = new Cutter_M(Global::getXFromIndex(sub_index), Global::getYFromIndex(sub_index), (direction + 2) % 4, parent);
    auto t = Global::map[sub_index];
    Global::map[sub_index] = sub_cutter;
    if (t) delete t;

    Cutter::connect(sub_cutter, &Cutter_M::erase, [=](){
        if (Global::map[index])
        {
            delete Global::map[index];
            Global::map[index] = nullptr;
        }

        if (Global::map[sub_index])
        {
            delete Global::map[sub_index];
            Global::map[sub_index] = nullptr;
        }
    });

    Cutter::connect(this, &Cutter::erase, [=](){
        if (Global::map[index])
        {
            delete Global::map[index];
            Global::map[index] = nullptr;
        }

        if (Global::map[sub_index])
        {
            delete Global::map[sub_index];
            Global::map[sub_index] = nullptr;
        }
    });

    void (Cutter::*func)(void) = &Cutter::function;
    connect(Global::game->game_engine[1], &QTimer::timeout, this, func);

    void (Cutter_M::*func_m)(void) = &Cutter_M::function;
    connect(this, &Cutter::output, sub_cutter, func_m);
}

Cutter::~Cutter()
{
    sub_cutter = nullptr;
}

void Cutter::show(QPainter &painter) const
{
    QPixmap cutter(Global::dest[CUTTER]);

    QTransform transform;
    transform.rotate(90 * get_direction());

    short first = get_direction() & 1, second = (get_direction() & 2) >> 1;
    painter.drawPixmap(X() - EDGE_LEN * (first ^ second) * first, Y() - EDGE_LEN * (first ^ second) * second, EDGE_LEN * (1 + (get_direction() & 1)), EDGE_LEN * (2 - (get_direction() & 1)), cutter.transformed(transform));
}

void placeCutter()
{
    QTimer *timer = new QTimer;
    timer->start(40);
    GameScene::connect(timer, &QTimer::timeout, [=]()
                       {
                           Global::game->update();
                       });

    Device::inLoop = true;
    Device::placeMachine = false;
    Device::typeofMachine = CUTTER;
    while (Device::inLoop)
    {
        Global::game->setMouseTracking(true);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
    }
    if (Device::placeMachine)
    {
        int index = Global::getIndex(Global::game->get_mouse_x(), Global::game->get_mouse_y());

        Square *temp = new Cutter(Global::getXFromIndex(index), Global::getYFromIndex(index), Device::direction, Global::game);

        Square *t = temp;
        temp = Global::map[index];
        Global::map[index] = t;

        if (temp) delete temp;
    }
    delete timer;
    Device::placeMachine = false;
    Device::typeofMachine = 0;
}

short Cutter::get_enter_direction() const
{
    return get_direction();
}

int Cutter::save() const
{
    return CUTTER | (get_direction() << TYPE_DIGITS);
}

int Cutter::function(Mine &ore)
{
    if (ore.get_type() == LEFT_HALF && to_produce >= 0)
    {
        int delta_x = (1 - ((get_direction() + 2) % 4 & 1)) * (((get_direction() + 2) % 4 >> 1) ? 1 : -1) * Global::conveyor_speed;
        ore.getx() += delta_x;
        int delta_y = ((get_direction() + 2) % 4 & 1) * (((get_direction() + 2) % 4 >> 1) ? 1 : -1) * Global::conveyor_speed;
        ore.gety() += delta_y;

        return 0;
    }
    else if (ore.is_seperable())
    {
        to_produce = 1;

        return 1;
    }
    else
    {
        to_produce = -1;

        return 1;
    }
}

void Cutter::function()
{
    int index = get_index(), sub_index = sub_cutter->get_index();
    int next_index = Global::getIndexinDirection(index, (get_direction() + 2) % 4);
    auto next_grid = Global::map[next_index];
    int sub_next_index = Global::getIndexinDirection(sub_index, sub_cutter->get_direction());
    auto sub_next_grid = Global::map[sub_next_index];
    if (next_grid && next_grid->__is_machine__() && static_cast<Machine *>(next_grid)->can_enter(index) && sub_next_grid && sub_next_grid->__is_machine__() && static_cast<Machine *>(sub_next_grid)->can_enter(sub_index))
    {
        if (to_produce == 1)
        {
            emit output();

            int offset = EDGE_LEN / 2 - Global::conveyor_speed;
            int dir = get_direction();
            int delta_x = (1 - (dir & 1)) * (dir >> 1 ? 1 : -1) * offset;
            int delta_y = (dir & 1) * (dir >> 1 ? 1 : -1) * offset;
            Mine *temp = new Mine(Global::getXFromIndex(next_index) + delta_x, Global::getYFromIndex(next_index) + delta_y, LEFT_HALF, Global::game);
            Global::all_mine_vec.push_back(temp);

            to_produce--;

            Abrasion();
        }
    }
}

bool Cutter::can_enter(int index) const
{
    return to_produce == 0 && index == get_enter_index();
}

void Cutter::Abrasion() const
{
    if (Global::coin_num >= MACHINE_ABRASION_FEE * (Global::cutter_upgrade + 1))
    {
        Global::coin_num -= MACHINE_ABRASION_FEE * (Global::cutter_upgrade + 1);
    }
}