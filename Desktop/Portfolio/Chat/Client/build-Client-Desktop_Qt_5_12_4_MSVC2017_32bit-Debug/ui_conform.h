/********************************************************************************
** Form generated from reading UI file 'conform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFORM_H
#define UI_CONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConForm
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *AddrLabel;
    QLineEdit *AddrEdit;
    QLabel *PortLabel;
    QLineEdit *PortEdit;
    QPushButton *ConnectBtn;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ConForm)
    {
        if (ConForm->objectName().isEmpty())
            ConForm->setObjectName(QString::fromUtf8("ConForm"));
        ConForm->resize(691, 478);
        gridLayout = new QGridLayout(ConForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(ConForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        splitter->addWidget(verticalLayoutWidget);
        verticalLayoutWidget_2 = new QWidget(splitter);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        AddrLabel = new QLabel(verticalLayoutWidget_2);
        AddrLabel->setObjectName(QString::fromUtf8("AddrLabel"));

        verticalLayout_2->addWidget(AddrLabel);

        AddrEdit = new QLineEdit(verticalLayoutWidget_2);
        AddrEdit->setObjectName(QString::fromUtf8("AddrEdit"));

        verticalLayout_2->addWidget(AddrEdit);

        PortLabel = new QLabel(verticalLayoutWidget_2);
        PortLabel->setObjectName(QString::fromUtf8("PortLabel"));

        verticalLayout_2->addWidget(PortLabel);

        PortEdit = new QLineEdit(verticalLayoutWidget_2);
        PortEdit->setObjectName(QString::fromUtf8("PortEdit"));

        verticalLayout_2->addWidget(PortEdit);

        ConnectBtn = new QPushButton(verticalLayoutWidget_2);
        ConnectBtn->setObjectName(QString::fromUtf8("ConnectBtn"));

        verticalLayout_2->addWidget(ConnectBtn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        splitter->addWidget(verticalLayoutWidget_2);
        verticalLayoutWidget_3 = new QWidget(splitter);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_2);

        splitter->addWidget(verticalLayoutWidget_3);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(ConForm);

        QMetaObject::connectSlotsByName(ConForm);
    } // setupUi

    void retranslateUi(QWidget *ConForm)
    {
        ConForm->setWindowTitle(QApplication::translate("ConForm", "Form", nullptr));
        AddrLabel->setText(QApplication::translate("ConForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Address:</span></p></body></html>", nullptr));
        PortLabel->setText(QApplication::translate("ConForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Port:</span></p></body></html>", nullptr));
        ConnectBtn->setText(QApplication::translate("ConForm", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConForm: public Ui_ConForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFORM_H
