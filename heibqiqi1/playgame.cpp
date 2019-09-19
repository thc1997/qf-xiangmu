#include "playgame.h"
#include "ui_playgame.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <Windows.h>
#include <QMessageBox>
#include <QApplication>

PlayGame::PlayGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayGame)
{
    ui->setupUi(this);

    this->setFixedSize(600, 400);

    ui->lcdNumber1->display(2);
    ui->lcdNumber2->display(2);
    ui->radioButton_white->setChecked(true);

    turn = true;
    flag = 0;
    time_tmp = time = 15;
    maxnum = 0;
    ttmpx = 0;
    ttmpy = 0;
    over = 0;
    bnum = 0;
    wnum = 0;

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

    connect(ui->pushButton_start, &QPushButton::clicked, [=](){
        timer->start(1000);
        this->PalyMusic();

        if(turn == true)
        {
            findgreen(chess, white1);
        }
        else
        {
            findgreen(chess, black1);
        }
        this->update();
    });

    connect(ui->pushButton_restart, &QPushButton::clicked, [=](){
        time_tmp = time;
        timer->stop();
        player->stop();
        InitChess();
        turn = true;
        ui->lcdNumber->display(time_tmp);
        this->update();
    });

    connect(ui->radioButton_black, &QRadioButton::clicked, [=](){
       turn = false;
       this->update();
    });

    connect(ui->radioButton_white, &QRadioButton::clicked, [=](){
       turn = true;
       this->update();
    });

    connect(ui->pushButton_end, &QPushButton::clicked, [=](){
        bnum = 0;
        wnum = 0;

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

        emit this->back();

    });

    InitChess();
}

PlayGame::~PlayGame()
{
    player->stop();
    delete ui;
}

void PlayGame::paintEvent(QPaintEvent *event)
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
            if(chess[i][j].status == black1)
            {
                QPainter *painter1 = new QPainter(this);
                QPixmap pix1;
                pix1.load(":/sucai/bc.png");
                painter->drawPixmap(chess[i][j].x, chess[i][j].y, 43, 43, pix1);
                bnum++;
            }
            else if(chess[i][j].status == white1)
            {
                QPainter *painter2 = new QPainter(this);
                QPixmap pix2;
                pix2.load(":/sucai/wc.png");
                painter->drawPixmap(chess[i][j].x, chess[i][j].y, 43, 43, pix2);
                wnum++;
            }
            else if(chess[i][j].status == green1)
            {
                QPainter *painter2 = new QPainter(this);
                QPixmap pix2;
                pix2.load(":/sucai/gc.png");
                painter->drawPixmap(chess[i][j].x, chess[i][j].y, 43, 43, pix2);
            }
        }
    }

    ui->lcdNumber1->display(bnum);
    ui->lcdNumber2->display(wnum);
}

void PlayGame::mousePressEvent(QMouseEvent *event)
{
    int overjudge = 0;
    int num = 0;

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
                    judgerole(i, j, white1);

                    this->repaint();

                    if(flag != 0)
                    {
                        this->luoziyin();

                        time_tmp = time;

                        if(judgeturn(black1) > 0)
                        {
                            Sleep(1000);

                            judgerole2(black1);

                            this->luoziyin();

                            bianligreen(chess);

                            findgreen(chess,white1);
                        }
                        else
                        {
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
                                findgreen(chess, white1);
                            }
                        }

                        this->update();
                    }
                    else
                    {
                        Beep();
                    }
                }
                else
                {
                    judgerole(i, j, black1);

                    this->repaint();

                    if(flag != 0)
                    {
                        this->luoziyin();

                        if(judgeturn(white1) > 0)
                        {
                            Sleep(1000);

                            judgerole2(black1);

                            this->luoziyin();

                            bianligreen(chess);

                            findgreen(chess,white1);
                        }
                        else
                        {
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
                                findgreen(chess, black1);
                            }
                        }

                        this->update();
                    }
                    else
                    {
                        Beep();
                    }
                }
            }
        }
    }

    bnum = 0;
    wnum = 0;
    over = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == black1)
            {
                bnum++;
            }
            else if(chess[i][j].status == white1)
            {
                wnum++;
            }
        }
    }
  if((wnum+bnum) == 64 && over == 0)
  {
      timer->stop();
      player->stop();
      over++;

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

int PlayGame::judgerole(int x, int y, STATUS1 status)
{
    int tmpx = x;
    int tmpy = y;
    maxnum =0;
    int posx = chess[tmpx][tmpy].x;
    int posy = chess[tmpx][tmpy].y;

    int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

    if(chess[tmpx][tmpy].status == black1 || chess[tmpx][tmpy].status == white1)
        return 0;

    for(int i=0; i<8; i++)
    {
        tmpx += dir[i][0];
        tmpy += dir[i][1];

        if(posx < 375 && posx >= 27 && posy < 375 && posy >= 27 && (chess[tmpx][tmpy].status != status) && (chess[tmpx][tmpy].status != empty1) && (chess[tmpx][tmpy].status != green1))
        {
            tmpx += dir[i][0];
            tmpy += dir[i][1];

            while(chess[tmpx][tmpy].x < 375 && chess[tmpx][tmpy].x >= 27 && chess[tmpx][tmpy].y < 375 && chess[tmpx][tmpy].y >= 27)
            {
                if(chess[tmpx][tmpy].status == empty1)
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

int PlayGame::judgerole1(int x, int y, STATUS1 status)
{
    int tmpx = x;
    int tmpy = y;
    maxnum = 0;
    int posx = chess[tmpx][tmpy].x;
    int posy = chess[tmpx][tmpy].y;

    int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

    if(chess[tmpx][tmpy].status != empty1)
        return 0;

    for(int i=0; i<8; i++)
    {
        tmpx += dir[i][0];
        tmpy += dir[i][1];

        if(posx < 375 && posx >= 27 && posy < 375 && posy >= 27 && (chess[tmpx][tmpy].status != status) && (chess[tmpx][tmpy].status != empty1) && (chess[tmpx][tmpy].status != green1))
        {
            tmpx += dir[i][0];
            tmpy += dir[i][1];

            while(chess[tmpx][tmpy].x < 375 && chess[tmpx][tmpy].x >= 27 && chess[tmpx][tmpy].y < 375 && chess[tmpx][tmpy].y >= 27)
            {
                if(chess[tmpx][tmpy].status == empty1)
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

void PlayGame::judgerole2(STATUS1 status)
{
    int mynum = 0;
    int maxnum_tmp = 0;
    int num = 0;
    maxnum = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            num = judgerole1(i, j, status);

            if(num  > maxnum_tmp)
            {
                maxnum_tmp = num;
                ttmpx = i;
                ttmpy = j;
            }
        }
    }

    if(maxnum_tmp == 0)
    {
        return;
    }
    else
    {
        judgerole(ttmpx, ttmpy, status);
    }

    return;

}

void PlayGame::InitChess()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if((i == 3 && j == 3) || (i ==4 && j == 4))
            {
                chess[i][j].x = 27+i*43;
                chess[i][j].y = 27+j*43;

                chess[i][j].status = black1;
            }
            else if((i == 3 && j == 4) || (i == 4 && j == 3))
            {
                chess[i][j].x = 27+i*43;
                chess[i][j].y = 27+j*43;

                chess[i][j].status = white1;
            }
            else
            {
                chess[i][j].x = 27+i*43;
                chess[i][j].y = 27+j*43;

                chess[i][j].status = empty1;
            }
        }
    }
}

void PlayGame::Beep()
{
    QApplication::beep();
}

void PlayGame::PalyMusic()
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

void PlayGame::luoziyin()
{
    QMediaPlaylist *playlist1 = new QMediaPlaylist;
    playlist1->addMedia(QUrl::fromLocalFile("../heibqiqi1/sucai/qizia.mp3"));

    QMediaPlayer *player1 = new QMediaPlayer;
    player1->setPlaylist(playlist1);

    player1->play();
}

int PlayGame::judgeresult(CHESS1 chess)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == black1)
            {
                bnum++;
            }
            else if(chess[i][j].status == white1)
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
    else if(bnum == wnum)
    {
        return 0;
    }
}

void PlayGame::bianligreen(CHESS1 chess)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(chess[i][j].status == green1)
            {
                chess[i][j].status = empty1;
            }

        }
    }
}

void PlayGame::findgreen(CHESS1 chess, STATUS1 status)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(judgerole1(i, j, status) > 0)
            {
                chess[i][j].status = green1;
            }

        }
    }
}

int PlayGame::judgeturn(STATUS1 status)
{
    num = 0;
    int num_tmp = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            num_tmp = judgerole1(i, j, status);
            num = num + num_tmp;
        }
    }

    return num;
}
