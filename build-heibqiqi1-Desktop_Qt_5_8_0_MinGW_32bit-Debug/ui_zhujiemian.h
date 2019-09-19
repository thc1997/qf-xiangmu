/********************************************************************************
** Form generated from reading UI file 'zhujiemian.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZHUJIEMIAN_H
#define UI_ZHUJIEMIAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZhuJieMian
{
public:
    QPushButton *pushButton_one;
    QPushButton *pushButton_two;

    void setupUi(QWidget *ZhuJieMian)
    {
        if (ZhuJieMian->objectName().isEmpty())
            ZhuJieMian->setObjectName(QStringLiteral("ZhuJieMian"));
        ZhuJieMian->resize(400, 300);
        pushButton_one = new QPushButton(ZhuJieMian);
        pushButton_one->setObjectName(QStringLiteral("pushButton_one"));
        pushButton_one->setGeometry(QRect(30, 310, 75, 23));
        pushButton_two = new QPushButton(ZhuJieMian);
        pushButton_two->setObjectName(QStringLiteral("pushButton_two"));
        pushButton_two->setGeometry(QRect(30, 360, 75, 23));

        retranslateUi(ZhuJieMian);

        QMetaObject::connectSlotsByName(ZhuJieMian);
    } // setupUi

    void retranslateUi(QWidget *ZhuJieMian)
    {
        ZhuJieMian->setWindowTitle(QApplication::translate("ZhuJieMian", "Form", Q_NULLPTR));
        pushButton_one->setText(QString());
        pushButton_two->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ZhuJieMian: public Ui_ZhuJieMian {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZHUJIEMIAN_H
