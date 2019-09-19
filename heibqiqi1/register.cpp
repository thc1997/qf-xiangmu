#include "register.h"
#include "ui_register.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");

    connect(ui->pushButton_back, &QPushButton::clicked, [=](){
        emit this->back();
    });

    connect(ui->pushButton, &QPushButton::clicked, [=](){
        this->user = ui->lineEdit->text();
        this->passwd1 = ui->lineEdit_2->text();
        this->passwd2 = ui->lineEdit_3->text();

        if(this->passwd1 == this->passwd2)
        {
            this->hide();
            emit this->back();
            QMessageBox::information(this, "注册成功", "注册成功!");

            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
        }
        else if(this->passwd1 != this->passwd2)
        {
            QMessageBox::critical(this, "错误", "两次输入密码不一致!请重新输入");
        }
    });
}

Register::~Register()
{
    delete ui;
}

void Register::paintEvent(QPaintEvent *event)
{
    QPainter *paintera = new QPainter(this);
    QPixmap pix;
    pix.load(":/sucai/02.jpg");
    paintera->drawPixmap(0, 0, this->width(), this->height(), pix);
}
