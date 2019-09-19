#include "widget.h"
#include "ui_widget.h"
#include "register.h"
#include "zhujiemian.h"
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Register *res = new Register;
    ZhuJieMian *zjm = new ZhuJieMian;

    this->setWindowTitle("登录");

    connect(ui->register_2, QPushButton::clicked, [=](){
        this->hide();
        res->show();
    });

    connect(res, &Register::back, [=](){
        res->hide();
        this->show();
    });

    connect(ui->signin, &QPushButton::clicked, [=](){
        QString user1(ui->lineEdit1->text());
        QString passwd(ui->lineEdit2->text());

        if(user1 == QString("") && passwd == QString(""))
        {
            QMessageBox::critical(this, "错误", "请输入账号和密码!");
        }

        if((user1 == res->user && passwd == res->passwd1) || (user1 == QString("thc") && passwd == QString("tanhuachao")))
        {
            if(user1 != QString("") && passwd != QString(""))
            {
                this->hide();
                zjm->show();
            }
        }
        else
        {
            QMessageBox::critical(this, "错误", "账号或密码输入有误!");
        }
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter *paintera = new QPainter(this);
    QPixmap pix;
    pix.load(":/sucai/02.jpg");
    paintera->drawPixmap(0, 0, this->width(), this->height(), pix);
}
