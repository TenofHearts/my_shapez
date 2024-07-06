#ifndef SUB_HUB_H
#define SUB_HUB_H

#include "machine.h"
#include "global.h"

/*
 * 此类为Hub类的基类，处理了交付中心的基本功能，不能独立存在
 */

class Sub_Hub : public Machine
{
    Q_OBJECT
public:
    Sub_Hub(int index, QWidget *parent = nullptr);
    ~Sub_Hub();
    bool can_enter(int) const override;
    int function(Mine &ore) override;
};

#endif // SUB_HUB_H
