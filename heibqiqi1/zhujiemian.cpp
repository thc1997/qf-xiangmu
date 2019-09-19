#include "zhujiemian.h"
#include "ui_zhujiemian.h"
#include "youxi.h"
#include "playgame.h"
#include <QPushButton>
#include <QPainter>

ZhuJieMian::ZhuJieMian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZhuJieMian)
{
    ui->setupUi(this);
    this->setWindowTitle("黑白棋");
    this->setFixedSize(350, 600);

    QIcon icon1(":/sucai/onep.png");
    ui->pushButton_one->setFixedSize(120, 30);
    ui->pushButton_one->setIcon(icon1);
    ui->pushButton_one->setIconSize(QSize(400, 300));

    QIcon icon2(":/sucai/twop.png");
    ui->pushButton_two->setFixedSize(120, 30);
    ui->pushButton_two->setIcon(icon2);
    ui->pushButton_two->setIconSize(QSize(400, 300));

    PlayGame *playgame = new PlayGame;
    connect(ui->pushButton_one, &QPushButton::clicked, [=](){
        this->hide();
        playgame->show();
        playgame->setWindowTitle("黑白棋_单人模式");
    });
    connect(playgame, &PlayGame::back, [=](){
       playgame->close();
       this->show();
    });

    YouXi *youxi = new YouXi;
    connect(ui->pushButton_two, &QPushButton::clicked, [=](){   
        this->hide();
        youxi->show();
        youxi->setWindowTitle("黑白棋_双人模式");
    });
    connect(youxi, &YouXi::back, [=](){
       youxi->close();
       this->show();
    });
}

ZhuJieMian::~ZhuJieMian()
{
    delete ui;
}

void ZhuJieMian::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    QPixmap pix;
    pix.load(":/sucai/01.jpg");
    painter->drawPixmap(0, 0, this->width(), this->height(), pix);
}

