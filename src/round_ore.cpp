#include "round_ore.h"
#include <global.h>

Round_Ore::Round_Ore(int x, int y, QWidget *parent)
    : Mine(x, y, parent)
{
    this->__set_seperable__(true);
}

Round_Ore::~Round_Ore()
{}

void Round_Ore::show(QPainter &painter) const
{
    painter.drawPixmap(QRect(this->X(), this->Y(), EDGE_LEN, EDGE_LEN), QPixmap(ROUND_ORE_DEST));
}
