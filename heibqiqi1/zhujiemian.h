#ifndef ZHUJIEMIAN_H
#define ZHUJIEMIAN_H

#include <QWidget>

namespace Ui {
class ZhuJieMian;
}

class ZhuJieMian : public QWidget
{
    Q_OBJECT

public:
    explicit ZhuJieMian(QWidget *parent = 0);
    ~ZhuJieMian();

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::ZhuJieMian *ui;
};

#endif // ZHUJIEMIAN_H
