#include "window.h"
#include "ui_window.h"
#include <QMessageBox>

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(ICON_DEST));
    setWindowTitle("shapez");
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);

    Global::player = new QMediaPlayer(this);
    Global::audio = new QAudioOutput(this);
    Global::audio->setVolume(static_cast<double>(Global::volumn) / 100);
    Global::player->setAudioOutput(Global::audio);
    Global::player->setSource(QUrl(BGM_DEST));
    Global::player->setLoops(QMediaPlayer::Infinite);
    Global::player->play();

    ui->label->move((this->width() - ui->label->width()) / 2, 100);
    ui->toolButton->move((this->width() - ui->toolButton->width()) / 2, 300);
    ui->toolButton_2->move((this->width() - ui->toolButton_2->width()) / 2, 400);

    connect(ui->toolButton_2, &QToolButton::clicked, [=](){
        // 读取存档，一次游戏只会调用一次，因此我认为没必要专门定义一个函数

        QString path = QFileDialog::getOpenFileName(this, "请选择存档", "./", "TXT Files(*.txt)");
        QFile file(path);
        // QFile file("./save.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(this, "Warning!!!", "找不到该存档，请创建新游戏！！！");
            qDebug() << "找不到该存档，请创建新游戏！！！";
        }
        else
        {
            QTextStream is(&file);

            try
            {
                is >> Global::coin_num;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                is >> Global::hub_std;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                is >> Global::ore_price;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }

                for (int i = 0; i < 240; ++i)
                {
                    is >> Global::init_map[i];
                    if (is.atEnd() || is.status() != QTextStream::Ok)
                    {
                        throw -1;
                    }
                }

                is >> Global::conveyor_upgrade;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                Global::conveyor_speed = Global::belt_speed[Global::conveyor_upgrade];
                is >> Global::miner_upgrade;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                Global::miner_speed = Global::produce_time[Global::miner_upgrade];
                is >> Global::cutter_upgrade;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                Global::cutter_speed = Global::produce_time[Global::cutter_upgrade];
                is >> Global::grid_upgrade;
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                Global::grid_std = Global::grid_upgrade;

                for (int i = 0; i < 3; ++i)
                {
                    is >> Level::cur[i];
                    if (is.atEnd() || is.status() != QTextStream::Ok)
                    {
                        throw -1;
                    }
                    is >> Level::goal[i];
                    if (is.atEnd() || is.status() != QTextStream::Ok)
                    {
                        throw -1;
                    }
                }
                is >> Level::cur[3];
                if (is.atEnd() || is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
                is >> Level::goal[3];
                if (is.status() != QTextStream::Ok)
                {
                    throw -1;
                }
            }
            catch (int)
            {
                QMessageBox::information(this, "Warning!!!", "存档已受损，将开始新游戏");

                Global::reset_map();
            }
        }
        file.close();
        startGame();
    });

    connect((ui->toolButton), &QToolButton::clicked, [=](){
        startGame();
    });
}

void Window::startGame()
{
    /*开始游戏时调用的函数*/
    Global::game = new GameScene();
    Global::pause = new PauseMenu();
    Global::shop = new ShopMenu();
    try
    {
        Global::game->LoadMap();
    } catch (int)
    {
        QMessageBox::information(this, "Warning!!!", "存档已受损，将开始新游戏");

        Global::reset_map();
        Global::game->LoadMap();
    }
    Global::game->setGeometry(this->geometry());
    Global::game->show();
    this->hide();
}

void Window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap background(BACKGROUND_DEST);

    painter.drawPixmap(this->rect(), background);
}

void Window::mousePressEvent(QMouseEvent *)
{
    // QString str = QString("鼠标释放了, x = %1, y = %2").arg(ev->position().x()).arg(ev->position().y());
    // qDebug() << str.toUtf8().data();
}

Window::~Window()
{
    delete ui;
    delete Global::player;
    delete Global::audio;
}
