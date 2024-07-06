#include "header/hub.h"

static const QVector<int> update_list{HUB_INDEX + 2,
                                      HUB_INDEX + 3,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS + 2,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS + 3,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 2,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 2 + 1,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 2 + 2,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 2 + 3,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 3,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 3 + 1,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 3 + 2,
                                      HUB_INDEX + NUM_OF_HORIZONTAL_GRIDS * 3 + 3};

Hub::Hub(int index, QWidget *parent)
    : Sub_Hub(index, parent)
{
    hub_mode = Global::hub_std;

    for (int i = 0; i < 2 * hub_mode; ++i)
    {
        CreateSubHub(index + i);
    }

    connect(this, &Hub::check_upgrade, this, &Hub::upgrade);
}

void Hub::CreateSubHub(int index)
{
    for (int i = (index == HUB_INDEX ? 1 : 0); i < 2 * hub_mode; ++i)
    {
        Global::map[index + i * NUM_OF_HORIZONTAL_GRIDS] = new Sub_Hub(index, this);
    }
}

Hub::~Hub()
{}

QRect Hub::rect() const
{
    return QRect(X(), Y(), EDGE_LEN * 2 * hub_mode, EDGE_LEN * 2 * hub_mode);
}

void Hub::show(QPainter &painter) const
{
    painter.drawPixmap(rect(), QPixmap(Global::dest[hub_mode + 5])); // 5是根据Global::dest[]中的初始化而调整的
}

int Hub::save() const
{
    return HUB;
}

void Hub::upgrade()
{
    if (hub_mode != Global::hub_std)
    {
        hub_mode = Global::hub_std;
        for (int index: update_list)
        {
            if (Global::map[index] && Global::map[index]->__is_machine__())
            {
                emit static_cast<Machine *>(Global::map[index])->erase();
            }
            Global::map[index] = new Sub_Hub(index, this);
        }
    }
}