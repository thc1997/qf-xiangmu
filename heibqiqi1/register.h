#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QString>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

    virtual void paintEvent(QPaintEvent *event);

    QString user;
    QString passwd1;
    QString passwd2;
signals:
    void back();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
