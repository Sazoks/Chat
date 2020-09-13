/********************************************************************************
** Form generated from reading UI file 'listchannels.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTCHANNELS_H
#define UI_LISTCHANNELS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListChannels
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *ConnectToChanBtn;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit;
    QPushButton *UploadMoreChan;
    QPushButton *pushButton;

    void setupUi(QWidget *ListChannels)
    {
        if (ListChannels->objectName().isEmpty())
            ListChannels->setObjectName(QString::fromUtf8("ListChannels"));
        ListChannels->resize(691, 478);
        gridLayout_2 = new QGridLayout(ListChannels);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ConnectToChanBtn = new QPushButton(ListChannels);
        ConnectToChanBtn->setObjectName(QString::fromUtf8("ConnectToChanBtn"));
        ConnectToChanBtn->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(ConnectToChanBtn, 4, 0, 1, 4);

        tableWidget = new QTableWidget(ListChannels);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 3, 0, 1, 4);

        lineEdit = new QLineEdit(ListChannels);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 2);

        UploadMoreChan = new QPushButton(ListChannels);
        UploadMoreChan->setObjectName(QString::fromUtf8("UploadMoreChan"));
        UploadMoreChan->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(UploadMoreChan, 0, 3, 1, 1);

        pushButton = new QPushButton(ListChannels);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        gridLayout->setColumnStretch(1, 6);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);

        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(ListChannels);

        QMetaObject::connectSlotsByName(ListChannels);
    } // setupUi

    void retranslateUi(QWidget *ListChannels)
    {
        ListChannels->setWindowTitle(QApplication::translate("ListChannels", "Form", nullptr));
        ConnectToChanBtn->setText(QApplication::translate("ListChannels", "Connect", nullptr));
        UploadMoreChan->setText(QApplication::translate("ListChannels", "Upload more channels", nullptr));
        pushButton->setText(QApplication::translate("ListChannels", "Search channel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListChannels: public Ui_ListChannels {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTCHANNELS_H
