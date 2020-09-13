/********************************************************************************
** Form generated from reading UI file 'messagewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEWINDOW_H
#define UI_MESSAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageWindow
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *MainLayout;
    QLineEdit *MsgEdit;
    QPushButton *SendMsgBtn;
    QTableWidget *tableWidget;

    void setupUi(QWidget *MessageWindow)
    {
        if (MessageWindow->objectName().isEmpty())
            MessageWindow->setObjectName(QString::fromUtf8("MessageWindow"));
        MessageWindow->resize(691, 478);
        gridLayout_2 = new QGridLayout(MessageWindow);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        MainLayout = new QGridLayout();
        MainLayout->setObjectName(QString::fromUtf8("MainLayout"));
        MsgEdit = new QLineEdit(MessageWindow);
        MsgEdit->setObjectName(QString::fromUtf8("MsgEdit"));
        MsgEdit->setMinimumSize(QSize(0, 35));

        MainLayout->addWidget(MsgEdit, 1, 0, 1, 1);

        SendMsgBtn = new QPushButton(MessageWindow);
        SendMsgBtn->setObjectName(QString::fromUtf8("SendMsgBtn"));
        SendMsgBtn->setMinimumSize(QSize(120, 35));

        MainLayout->addWidget(SendMsgBtn, 1, 1, 1, 1);

        tableWidget = new QTableWidget(MessageWindow);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setColumnCount(0);

        MainLayout->addWidget(tableWidget, 0, 0, 1, 2);


        gridLayout_2->addLayout(MainLayout, 0, 0, 1, 1);


        retranslateUi(MessageWindow);

        QMetaObject::connectSlotsByName(MessageWindow);
    } // setupUi

    void retranslateUi(QWidget *MessageWindow)
    {
        MessageWindow->setWindowTitle(QApplication::translate("MessageWindow", "Form", nullptr));
        SendMsgBtn->setText(QApplication::translate("MessageWindow", "Send msg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageWindow: public Ui_MessageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEWINDOW_H
