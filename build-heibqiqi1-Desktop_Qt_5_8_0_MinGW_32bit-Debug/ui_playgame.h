/********************************************************************************
** Form generated from reading UI file 'playgame.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYGAME_H
#define UI_PLAYGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayGame
{
public:
    QPushButton *pushButton_start;
    QPushButton *pushButton_end;
    QPushButton *pushButton_restart;
    QLCDNumber *lcdNumber1;
    QLCDNumber *lcdNumber2;
    QLCDNumber *lcdNumber;
    QGroupBox *First;
    QRadioButton *radioButton_white;
    QRadioButton *radioButton_black;
    QComboBox *comboBox;

    void setupUi(QWidget *PlayGame)
    {
        if (PlayGame->objectName().isEmpty())
            PlayGame->setObjectName(QStringLiteral("PlayGame"));
        PlayGame->resize(700, 572);
        pushButton_start = new QPushButton(PlayGame);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setGeometry(QRect(500, 110, 75, 23));
        pushButton_end = new QPushButton(PlayGame);
        pushButton_end->setObjectName(QStringLiteral("pushButton_end"));
        pushButton_end->setGeometry(QRect(500, 140, 75, 23));
        pushButton_restart = new QPushButton(PlayGame);
        pushButton_restart->setObjectName(QStringLiteral("pushButton_restart"));
        pushButton_restart->setGeometry(QRect(500, 170, 75, 23));
        lcdNumber1 = new QLCDNumber(PlayGame);
        lcdNumber1->setObjectName(QStringLiteral("lcdNumber1"));
        lcdNumber1->setGeometry(QRect(400, 30, 65, 70));
        lcdNumber1->setFrameShape(QFrame::NoFrame);
        lcdNumber2 = new QLCDNumber(PlayGame);
        lcdNumber2->setObjectName(QStringLiteral("lcdNumber2"));
        lcdNumber2->setGeometry(QRect(400, 320, 65, 70));
        lcdNumber2->setFrameShape(QFrame::NoFrame);
        lcdNumber = new QLCDNumber(PlayGame);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(343, 152, 121, 91));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcdNumber->setPalette(palette);
        lcdNumber->setFrameShape(QFrame::NoFrame);
        First = new QGroupBox(PlayGame);
        First->setObjectName(QStringLiteral("First"));
        First->setGeometry(QRect(500, 240, 120, 80));
        radioButton_white = new QRadioButton(First);
        radioButton_white->setObjectName(QStringLiteral("radioButton_white"));
        radioButton_white->setGeometry(QRect(10, 20, 89, 16));
        radioButton_black = new QRadioButton(First);
        radioButton_black->setObjectName(QStringLiteral("radioButton_black"));
        radioButton_black->setGeometry(QRect(10, 50, 89, 16));
        comboBox = new QComboBox(PlayGame);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(500, 200, 73, 22));

        retranslateUi(PlayGame);

        QMetaObject::connectSlotsByName(PlayGame);
    } // setupUi

    void retranslateUi(QWidget *PlayGame)
    {
        PlayGame->setWindowTitle(QApplication::translate("PlayGame", "Form", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("PlayGame", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_end->setText(QApplication::translate("PlayGame", "\347\273\223\346\235\237", Q_NULLPTR));
        pushButton_restart->setText(QApplication::translate("PlayGame", "\351\207\215\346\226\260\345\274\200\345\247\213", Q_NULLPTR));
        First->setTitle(QString());
        radioButton_white->setText(QApplication::translate("PlayGame", "\347\231\275\345\255\220", Q_NULLPTR));
        radioButton_black->setText(QApplication::translate("PlayGame", "\351\273\221\345\255\220", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PlayGame", "\345\210\235\347\272\247", Q_NULLPTR)
         << QApplication::translate("PlayGame", "\344\270\255\347\272\247", Q_NULLPTR)
         << QApplication::translate("PlayGame", "\351\253\230\347\272\247", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class PlayGame: public Ui_PlayGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYGAME_H
