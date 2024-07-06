#ifndef HUB_H
#define HUB_H

#include "sub_hub.h"
#include "global.h"

/*
 * 交付中心的左上角，一局游戏仅会实例化一个对象，并且无法删除
 *
 * 控制交付中心升级等行为
 */

class Hub : public Sub_Hub
{
    Q_OBJECT
    int hub_mode;
public:
    Hub(int index = HUB_INDEX, QWidget *parent = nullptr);
    ~Hub();
    void show(QPainter &) const override;
    QRect rect() const;
    int save() const override;
    void CreateSubHub(int index);
    void upgrade();
signals:
    void check_upgrade();
};

#endif // HUB_H
