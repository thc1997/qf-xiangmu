#ifndef YOUXI_H
#define YOUXI_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QApplication>
#include <QTimer>

typedef enum {empty, black, white, green} STATUS;
typedef struct qizi
{
    int x;
    int y;

    STATUS status;

}QIZI;
typedef QIZI CHESS[8][8];

namespace Ui {
class YouXi;
}

class YouXi : public QWidget
{
    Q_OBJECT

public:
    explicit YouXi(QWidget *parent = 0);
    ~YouXi();

    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);  
    //virtual void timerEvent(QTimerEvent *e);

    int judgerole(int x, int y, STATUS status);
    int judgerole1(int x, int y, STATUS status);
    void InitChess(void);
    void Beep();
    void PalyMusic();
    void luoziyin();
    int judgeresult(CHESS chess);
    void bianligreen(CHESS chess);
    void findgreen(CHESS chess, STATUS status);
    int judgeturn(STATUS status);

    CHESS chess;
    bool turn;
    int flag;
    int time;
    int time_tmp;
    int end_time;
    int maxnum;
    int over;
    int bnum;
    int wnum;
    bool judge;
    int num;
    QTimer *timer = new QTimer;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;


signals:
    void back();

private:
    Ui::YouXi *ui;
};


#endif // YOUXI_H
