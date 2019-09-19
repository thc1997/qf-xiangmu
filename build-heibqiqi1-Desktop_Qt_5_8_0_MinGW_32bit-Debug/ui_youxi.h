/********************************************************************************
** Form generated from reading UI file 'youxi.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YOUXI_H
#define UI_YOUXI_H

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

class Ui_YouXi
{
public:
    QLCDNumber *lcdNumber1;
    QLCDNumber *lcdNumber2;
    QLCDNumber *lcdNumber;
    QPushButton *pushButton_start;
    QPushButton *pushButton_end;
    QPushButton *pushButton_restart;
    QGroupBox *groupBox;
    QRadioButton *radioButton_White;
    QRadioButton *radioButton_Black;
    QComboBox *comboBox;

    void setupUi(QWidget *YouXi)
    {
        if (YouXi->objectName().isEmpty())
            YouXi->setObjectName(QStringLiteral("YouXi"));
        YouXi->resize(761, 411);
        lcdNumber1 = new QLCDNumber(YouXi);
        lcdNumber1->setObjectName(QStringLiteral("lcdNumber1"));
        lcdNumber1->setGeometry(QRect(400, 320, 65, 70));
        lcdNumber1->setFrameShape(QFrame::NoFrame);
        lcdNumber2 = new QLCDNumber(YouXi);
        lcdNumber2->setObjectName(QStringLiteral("lcdNumber2"));
        lcdNumber2->setGeometry(QRect(400, 30, 65, 70));
        lcdNumber2->setFrameShape(QFrame::NoFrame);
        lcdNumber = new QLCDNumber(YouXi);
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
        pushButton_start = new QPushButton(YouXi);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setGeometry(QRect(500, 110, 75, 23));
        pushButton_end = new QPushButton(YouXi);
        pushButton_end->setObjectName(QStringLiteral("pushButton_end"));
        pushButton_end->setGeometry(QRect(500, 140, 75, 23));
        pushButton_restart = new QPushButton(YouXi);
        pushButton_restart->setObjectName(QStringLiteral("pushButton_restart"));
        pushButton_restart->setGeometry(QRect(500, 170, 75, 23));
        groupBox = new QGroupBox(YouXi);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(490, 240, 120, 80));
        radioButton_White = new QRadioButton(groupBox);
        radioButton_White->setObjectName(QStringLiteral("radioButton_White"));
        radioButton_White->setGeometry(QRect(20, 20, 89, 16));
        radioButton_Black = new QRadioButton(groupBox);
        radioButton_Black->setObjectName(QStringLiteral("radioButton_Black"));
        radioButton_Black->setGeometry(QRect(20, 40, 89, 16));
        comboBox = new QComboBox(YouXi);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(500, 200, 73, 22));

        retranslateUi(YouXi);

        QMetaObject::connectSlotsByName(YouXi);
    } // setupUi

    void retranslateUi(QWidget *YouXi)
    {
        YouXi->setWindowTitle(QApplication::translate("YouXi", "Form", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("YouXi", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_end->setText(QApplication::translate("YouXi", "\347\273\223\346\235\237", Q_NULLPTR));
        pushButton_restart->setText(QApplication::translate("YouXi", "\351\207\215\346\226\260\345\274\200\345\247\213", Q_NULLPTR));
        groupBox->setTitle(QString());
        radioButton_White->setText(QApplication::translate("YouXi", "\347\231\275\345\255\220", Q_NULLPTR));
        radioButton_Black->setText(QApplication::translate("YouXi", "\351\273\221\345\255\220", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("YouXi", "\345\210\235\347\272\247", Q_NULLPTR)
         << QApplication::translate("YouXi", "\344\270\255\347\272\247", Q_NULLPTR)
         << QApplication::translate("YouXi", "\351\253\230\347\272\247", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class YouXi: public Ui_YouXi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YOUXI_H
