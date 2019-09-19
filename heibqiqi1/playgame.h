#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <QWidget>
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>

typedef enum {empty1, black1, white1, green1} STATUS1;
typedef struct qizi1
{
    int x;
    int y;

    STATUS1 status;

}QIZI1;
typedef QIZI1 CHESS1[8][8];

namespace Ui {
class PlayGame;
}

class PlayGame : public QWidget
{
    Q_OBJECT

public:
    explicit PlayGame(QWidget *parent = 0);
    ~PlayGame();

    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    //virtual void timerEvent(QTimerEvent *e);

    int judgerole(int x, int y, STATUS1 status);
    int judgerole1(int x, int y, STATUS1 status);
    void judgerole2(STATUS1 status);
    void InitChess(void);
    void Beep();
    void PalyMusic();
    void luoziyin();
    int judgeresult(CHESS1 chess);
    void bianligreen(CHESS1 chess);
    void findgreen(CHESS1 chess, STATUS1 status);
    int judgeturn(STATUS1 status);

    CHESS1 chess;
    bool turn;
    int flag;
    int time;
    int time_tmp;
    int end_time;
    int maxnum;
    int ttmpx;
    int ttmpy;
    int over;
    int bnum;
    int wnum;
    bool judge;
    int num;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    QTimer *timer = new QTimer;

signals:
    void back();

private:
    Ui::PlayGame *ui;
};

#endif // PLAYGAME_H
