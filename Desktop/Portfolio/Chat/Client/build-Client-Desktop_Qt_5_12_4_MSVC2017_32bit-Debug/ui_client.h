/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(400, 300);
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Client->addToolBar(mainToolBar);
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Client->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Client->setStatusBar(statusBar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
