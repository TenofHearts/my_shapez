#include "pausemenu.h"
#include "ui_pausemenu.h"
#include "gamescene.h"

PauseMenu::PauseMenu(QWidget *parent)
    : QWidget{parent}, ui(new Ui::PauseMenu)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(ICON_DEST));
    setWindowTitle("Pause");
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);

    ui->label->setFixedSize(680, 480);
    ui->label->setText("                            关于本作   \n\n"
                       "    这里是shapez的小demo，类似异形工厂的小游戏。是c++高程大作业，作者Yj。\n\n"
                       "基本操作:\n"
                       "    点击按钮来放置建筑，使用键盘R键旋转建筑方向，鼠标右键撤销放置建筑操作。\n\n"
                       "共有5种建筑：（机器使用时会有损耗，因此需要扣除一定的金币）\n"
                       "    开采器：放置在矿地上后可开采出物品。请注意输出物品的方向。\n"
                       "    传送带：运送物品。请注意运送物品的方向。\n"
                       "    切割机：将物品纵向切开并分别输出。如果只需要其中一半的物品，那么需要使用\n垃圾桶清除另一半物品，否则切割机会停止工作。\n"
                       "    垃圾桶：可以从所有四个方向上输入物品并永久清除它们。\n"
                       "    转向器：可以将输入的矿旋转180度。\n"
                       "    合并器：将两条轨道合并为一道。\n\n"
                       "获胜条件: 每个关卡需收集一定数量的物品。注意：不符合要求或超量的矿会收到惩罚\n"
                       "    可以升级开采器、传送带或切割机中的一个建筑。请注意，升级效果仅在当前关卡\n有效。\n"
                       "    通过消耗金币，可以在商店中全局强化交付中心的大小、开采物所在地块的数量等。\n\n"
                       "                            感谢游玩！");

    ui->horizontalSlider->setValue(Global::volumn);

    connect(ui->continue_btn, &QToolButton::clicked, [=](){
        Global::game->setGeometry(this->geometry());
        Global::game->show();
        Global::pause->hide();
    });

    connect(ui->save_btn, &QToolButton::clicked, [=](){
        QFile file("./save.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            exit(-1);
        }
        QTextStream out(&file);
        out << Global::coin_num << " ";
        out << Global::hub_std << " ";
        out << Global::ore_price << " ";
        out << "\n";
        for (auto &&sqr: Global::map)
        {
            int id = 0;
            if (sqr)
            {
                id = sqr->save();
            }
            out << id << ' ';
        }
        out << "\n";

        out << Global::conveyor_upgrade << ' ';
        out << Global::miner_upgrade << ' ';
        out << Global::cutter_upgrade << ' ';
        out << Global::grid_upgrade << " ";
        out << "\n";

        for (int i = 0; i < 4; ++i)
        {
            out << Level::cur[i] << " " << Level::goal[i] << " ";
        }
        out << "\n";

        file.close();

        QMessageBox::information(this, "Info", "存档成功！");
    });

    connect(ui->horizontalSlider, &QSlider::sliderMoved, [&](){
        Global::volumn = ui->horizontalSlider->value();
        Global::audio->setVolume(static_cast<double>(Global::volumn) / 100);
    });
}

PauseMenu::~PauseMenu()
{
    delete ui;
}

void PauseMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(this->rect(), QPixmap(BACKGROUND_DEST));
}
