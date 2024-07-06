#include "header/shopmenu.h"
#include "ui_shopmenu.h"
#include <header/gamescene.h>

ShopMenu::ShopMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShopMenu)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(ICON_DEST));
    setWindowTitle("Shop");
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    connect(ui->continue_btn, &QToolButton::clicked, [=]() {
        Global::game->setGeometry(this->geometry());
        Global::game->show();
        this->hide();
    });

    connect(ui->belt_upgrade_btn, &QToolButton::clicked, [=]() {
        if (!Global::conveyor_upgrade)
        {
            if (Global::coin_num >= TEMP_PRICE)
            {
                Global::conveyor_speed = FAST_BELT_SPEED;
                Global::conveyor_upgrade = 1;
                Global::coin_num -= TEMP_PRICE;
                ui->coin_count_label->setText(Global::display_coin());
            }
            else
            {
                QMessageBox::information(this, "Info", "货币不足，无法购买");
            }
        }
        else
        {
            QMessageBox::information(this, "Info", "传送带已升级");
        }
    });

    connect(ui->cutter_upgrade_btn, &QToolButton::clicked, [=]() {
        if (!Global::cutter_upgrade)
        {
            if (Global::coin_num >= TEMP_PRICE)
            {
                Global::cutter_speed = FAST_PRODUCE_TIME;
                Global::cutter_upgrade = 1;
                Global::coin_num -= TEMP_PRICE;
                ui->coin_count_label->setText(Global::display_coin());
            }
            else
            {
                QMessageBox::information(this, "Info", "货币不足，无法购买");
            }
        }
        else
        {
            QMessageBox::information(this, "Info", "切割机已升级");
        }
    });

    connect(ui->miner_upgrade_btn, &QToolButton::clicked, [=]() {
        if (!Global::miner_upgrade)
        {
            if (Global::coin_num >= TEMP_PRICE)
            {
                Global::miner_speed = FAST_PRODUCE_TIME;
                Global::miner_upgrade = 1;
                Global::coin_num -= TEMP_PRICE;
                ui->coin_count_label->setText(Global::display_coin());
            }
            else
            {
                QMessageBox::information(this, "Info", "货币不足，无法购买");
            }
        }
        else
        {
            QMessageBox::information(this, "Info", "挖矿机已升级");
        }
    });

    connect(ui->hub_upgrade_btn, &QToolButton::clicked, [=](){
        if (Global::hub_std == SMALL_HUB)
        {
            if (Global::coin_num >= PERMANENT_PRICE)
            {
                Global::hub_std = BIG_HUB;
                Global::coin_num -= PERMANENT_PRICE;
                ui->coin_count_label->setText(Global::display_coin());
            }
            else
            {
                QMessageBox::information(this, "Info", "货币不足，无法购买");
            }
        }
        else
        {
            QMessageBox::information(this, "Info", "交付中心已升级");
        }
    });

    connect(ui->increase_ore_value_btn, &QToolButton::clicked, [=](){
        if (Global::ore_price == LOW_PRICE)
        {
            if (Global::coin_num >= PERMANENT_PRICE)
            {
                Global::ore_price = HIGH_PRICE;
                Global::coin_num -= PERMANENT_PRICE;
                ui->coin_count_label->setText(Global::display_coin());
            }
            else
            {
                QMessageBox::information(this, "Info", "货币不足，无法购买");
            }
        }
        else
        {
            QMessageBox::information(this, "Info", "矿物价格已升级");
        }
    });

    connect(ui->increase_ore_num_btn, &QToolButton::clicked, [=](){
        if (!Global::grid_upgrade)
        {
            if (Global::coin_num >= PERMANENT_PRICE)
            {
                Global::grid_upgrade = 1;
                Global::coin_num -= PERMANENT_PRICE;
                ui->coin_count_label->setText(Global::display_coin());
            }
            else
            {
                QMessageBox::information(this, "Info", "货币不足，无法购买");
            }
        }
        else
        {
            QMessageBox::information(this, "Info", "矿物数量已升级");
        }
    });
}

ShopMenu::~ShopMenu()
{
    delete ui;
}

void ShopMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(BACKGROUND_DEST));
}

void ShopMenu::showEvent(QShowEvent *)
{
    ui->coin_count_label->setText(Global::display_coin());
}