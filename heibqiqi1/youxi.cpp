#include "youxi.h"
#include "ui_youxi.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QMessageBox>

YouXi::YouXi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YouXi)
{
    ui->setupUi(this);

    this->setFixedSize(600, 400);

    ui->lcdNumber1->display(2);
    ui->lcdNumber2->display(2);
    ui->radioButton_White->setChecked(true);
    ui->comboBox->setCurrentIndex(0);

    turn = true;
    flag = 0;
    time_tmp = time = 15;
    maxnum = 0;
    over = 0;
    num = 0;

    connect(timer, &QTimer::timeout, [=](){
        ui->lcdNumber->display(time_tmp--);
        end_time = (int)ui->lcdNumber->value();

        if(end_time == 0)
        {
            time_tmp = time;
            turn = !turn;

            this->update();
        }
    });

    void (QComboBox::*p)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBox, p, [=](int index){
        if(index == 0)
        {
            time = 15;
            time_tmp = time;
        }
        else if(index == 1)
        {
            time = 10;
            time_tmp = time;
        }
        else if(index == 2)
        {
            time = 5;
            time_tmp = time;
        }
    });

    connect(ui->pushButton_start, &QPushButton::clicked, [=](){
        timer->start(1000);
        this->PalyMusic();

        if(turn == true)
        {
            findgreen(chess, white);
        }
        else
        {
            findgreen(chess, black);
        }

        this->update();
    });

    connect(ui->pushButton_restart, &QPushButton::clicked, [=](){
        time_tmp = time;
        InitChess();
        timer->stop();
        player->stop();
        ui->lcdNumber->display(time_tmp);
        turn = true;
        this->update();
    });

    connect(ui->pushButton_end, &QPushButton::clicked, [=](){
        bnum = 0;
        wnum = 0;

        player->stop();
        timer->stop();

        if(judgeresult(chess) == -1)
        {
            QMessageBox::information(this, "结果", "白棋获胜");
        }
        else if(judgeresult(chess) == 1)
        {
            QMessageBox::information(this, "结果", "黑棋获胜");
        }
        else if(judgeresult(chess) == 0)
        {
            QMessageBox::information(this, "结果", "平局");
        }

        emit this->back();
    });

    connect(ui->radioButton_Black, &QRadioButton::clicked, [=](){
        turn = false;
        this->repaint();
    });

    connect(ui->radioButton_White, &QRadioButton::clicked, [=](){
        turn = true;
        this->repaint();
    });

    InitChess();
}

YouXi::~YouXi()
{
    player->stop();
    delete ui;
}

int YouXi::judgerole(int x, int y, STATUS status)
{
   int tmpx = x;
   int tmpy = y;

   int posx = chess[tmpx][tmpy].x;
   int posy = chess[tmpx][tmpy].y;

   int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

   if(chess[tmpx][tmpy].status == black || chess[tmpx][tmpy].status == white)
       return 0;

   for(int i=0; i<8; i++)
   {
       tmpx += dir[i][0];
       tmpy += dir[i][1];

       if(posx < 375 && posx >= 27 && posy < 375 && posy >= 27 && (chess[tmpx][tmpy].status != status) && (chess[tmpx][tmpy].status != empty) && (chess[tmpx][tmpy].status != green))
       {
           tmpx += dir[i][0];
           tmpy += dir[i][1];

           while(chess[tmpx][tmpy].x < 375 && chess[tmpx][tmpy].x >= 27 && chess[tmpx][tmpy].y < 375 && chess[tmpx][tmpy].y >= 27)
           {
               if(chess[tmpx][tmpy].status == empty)
               {
                   break;
               }

               else if(chess[tmpx][tmpy].status == status)
               {
                   chess[x][y].status = status;

                   while(tmpx != x || tmpy !=y)
                   {
                       tmpx -= dir[i][0];
                       tmpy -= dir[i][1];

                       chess[tmpx][tmpy].status = status;
                       flag++;
                       maxnum++;

                   }

                   break;
               }
               else
               {
                   tmpx += dir[i][0];
                   tmpy += dir[i][1];
               }
           }
       }

       tmpx = x;
       tmpy = y;
   }

   return maxnum;
}

int YouXi::judgerole1(int x, int y, STATUS status)
{
    int tmpx = x;
    int tmpy = y;
    maxnum = 0;
    int posx = chess[tmpx][tmpy].x;
    int posy = chess[tmpx][tmpy].y;

    int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

    if(chess[tmpx][tmpy].status != empty)
        return 0;

    for(int i=0; i<8; i++)
    {
        tmpx += dir[i][0];
        tmpy += dir[i][1];

        if(posx < 375 && posx >= 27 && posy < 375 && posy >= 27 && (chess[tmpx][tmpy].status != status) && (chess[tmpx][tmpy].status != empty) && (chess[tmpx][tmpy].status != green))
        {
            tmpx += dir[i][0];
            tmpy += dir[i][1];

            while(chess[tmpx][tmpy].x < 375 && chess[tmpx][tmpy].x >= 27 && chess[tmpx][tmpy].y < 375 && chess[tmpx][tmpy].y >= 27)
            {
                if(chess[tmpx][tmpy].status == empty)
                {
                    break;
                }

                else if(chess[tmpx][tmpy].status == status)
                {
                    while(tmpx != x || tmpy !=y)
                    {

                        tmpx -= dir[i][0];
                        tmpy -= dir[i][1];
                        maxnum++;
                    }

                    break;
                }
                else
                {
                    tmpx += dir[i][0];
                    tmpy += dir[i][1];
                }
            }
        }

        tmpx = x;
        tmpy = y;
    }

    return maxnum;
}

void YouXi::InitChess()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if((i == 3 && j == 3) || (i ==4 && j == 4))
            {
                chess[i][j].x = 27+i*43;
                chess[i][j].y = 27+j*43;

                chess[i][j].status = black;
            }
            else if((i == 3 && j == 4) || (i == 4 && j == 3))
            {
                chess[i][j].x = 27+i*43;
                chess[i][j].y = 27+j*43;

                chess[i][j].status = white;
            }
            else
            {
                chess[i][j].x = 27+i*43;
                chess[i][j].y = 27+j*43;

                chess[i][j].status = empty;
            }
        }
    }
}

void YouXi::Beep()
{
    QApplication::beep();
}

void YouXi::PalyMusic()
{
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("../heibqiqi1/sucai/music.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("../heibqiqi1/sucai/music.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("../heibqiqi1/sucai/music.mp3"));
    playlist->setCurrentIndex(1);

    player = new QMediaPlayer;
    player->setPlaylist(playlist);

    player->play();
}

void YouXi::luoziyin()
{
    QMediaPlaylist *playlist1 = new QMediaPlaylist;
    playlist1->addMedia(QUrl::fromLocalFile("../heibqiqi1/sucai/qizia.mp3"));

    QMediaPlayer *player1 = new QMediaPlayer;
    player1->setPlaylist(playlist1);

    player1->play();
}

int YouXi::judgeresult(CHESS chess)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == black)
            {
                bnum++;
            }
            else if(chess[i][j].status == white)
            {
                wnum++;
            }
        }
    }

    if(bnum > wnum)
    {
        return 1;
    }
    else if(bnum < wnum)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void YouXi::bianligreen(CHESS chess)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == green)
            {
                chess[i][j].status = empty;
            }

        }
    }
}

void YouXi::findgreen(CHESS chess, STATUS status)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(judgerole1(i, j, status) > 0)
            {
                chess[i][j].status = green;
            }
        }
    }
}

int YouXi::judgeturn(STATUS status)
{
    int num_tmp = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            num_tmp = judgerole1(i, j, status);
            num = num_tmp;
        }
    }

    return num;
}

void YouXi::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    QPixmap pix;
    pix.load(":/sucai/qipan");
    painter->drawPixmap(0, 0, 400, 400, pix);

    QPixmap pix1;
    pix1.load(":/sucai/bc.png");
    painter->drawPixmap(500, 30, 65, 70, pix1);

    QPixmap pix2;
    pix2.load(":/sucai/wc.png");
    painter->drawPixmap(500, 320, 65, 70, pix2);

    if(turn == true)
    {
       painter->setPen(Qt::red);
       painter->drawRect(500, 320, 65, 70);
    }
    else
    {
       painter->setPen(Qt::red);
       painter->drawRect(500, 30, 65, 70);
    }

    bnum = 0;
    wnum = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == black)
            {
                QPainter *painter1 = new QPainter(this);
                QPixmap pix1;
                pix1.load(":/sucai/bc.png");
                painter->drawPixmap(chess[i][j].x, chess[i][j].y, 43, 43, pix1);
                bnum++;
            }
            else if(chess[i][j].status == white)
            {
                QPainter *painter2 = new QPainter(this);
                QPixmap pix2;
                pix2.load(":/sucai/wc.png");
                painter->drawPixmap(chess[i][j].x, chess[i][j].y, 43, 43, pix2);
                wnum++;
            }
            else if(chess[i][j].status == green)
            {
                QPainter *painter2 = new QPainter(this);
                QPixmap pix2;
                pix2.load(":/sucai/gc.png");
                painter->drawPixmap(chess[i][j].x, chess[i][j].y, 43, 43, pix2);
            }
        }
    }

    ui->lcdNumber1->display(wnum);
    ui->lcdNumber2->display(bnum);
}

void YouXi::mousePressEvent(QMouseEvent *event)
{
    num = 0;
    judge = 0;
    bnum = 0;
    wnum = 0;
    over = 0;
    int pos_x = event->x();
    int pos_y = event->y();

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(pos_x>chess[i][j].x && chess[i][j].x+43 > pos_x && pos_y>chess[i][j].y && chess[i][j].y+43 > pos_y)
            {
                flag = 0;

                if(turn == true)
                {
                    judgerole(i, j, white);

                    if(flag != 0)
                    {
                        this->luoziyin();

                        if(judgeturn(black) > 0)
                        {
                            bianligreen(chess);

                            findgreen(chess, black);
                        }
                        else
                        {
                            turn = !turn;
                            flag = 0;
                            judge++;

                            if(judge == 2)
                            {
                                timer->stop();
                                player->stop();

                                if(judgeresult(chess) == -1)
                                {
                                    QMessageBox::information(this, "结果", "白棋获胜");
                                }
                                else if(judgeresult(chess) == 1)
                                {
                                    QMessageBox::information(this, "结果", "黑棋获胜");
                                }
                                else if(judgeresult(chess) == 0)
                                {
                                    QMessageBox::information(this, "结果", "平局");
                                }
                            }
                            else
                            {
                                bianligreen(chess);
                                findgreen(chess, black);
                            }
                            this->update();
                        }
                    }
                    else
                    {
                        this->Beep();
                    }
                }
                else
                {
                    judgerole(i, j, black);

                    if(flag != 0)
                    {
                        this->luoziyin();

                        if(judgeturn(white) > 0)
                        {
                            bianligreen(chess);
                            findgreen(chess, white);
                        }
                        else
                        {
                            turn = !turn;
                            flag = 0;
                            judge++;

                            if(judge == 2)
                            {
                                if(judgeresult(chess) == -1)
                                {
                                    QMessageBox::information(this, "结果", "白棋获胜");
                                }
                                else if(judgeresult(chess) == 1)
                                {
                                    QMessageBox::information(this, "结果", "黑棋获胜");
                                }
                                else if(judgeresult(chess) == 0)
                                {
                                    QMessageBox::information(this, "结果", "平局");
                                }

                                timer->stop();
                                player->stop();
                            }
                            else
                            {
                                bianligreen(chess);
                                findgreen(chess, white);
                            }
                            this->update();
                        }
                    }
                    else
                    {
                        this->Beep();
                    }
                }

                if(flag != 0)
                {
                    turn = !turn;
                    time_tmp = time;;
                }
            }
        }
    }

    this->update();

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == black)
            {
                bnum++;
            }
            else if(chess[i][j].status == white)
            {
                wnum++;
            }
        }
    }

    if((bnum+wnum) == 64 && over == 0)
    {
        timer->stop();
        player->stop();

        if(wnum > bnum)
        {
            QMessageBox::information(this, "结果", "白棋获胜");
        }
        else if(wnum < bnum)
        {
            QMessageBox::information(this, "结果", "黑棋获胜");
        }
        else if(wnum == bnum)
        {
            QMessageBox::information(this, "结果", "平局");
        }
    }
}









