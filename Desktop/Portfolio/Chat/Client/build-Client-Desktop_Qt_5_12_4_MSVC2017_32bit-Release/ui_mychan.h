/********************************************************************************
** Form generated from reading UI file 'mychan.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCHAN_H
#define UI_MYCHAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyChan
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridL;
    QLineEdit *NewPassEdit;
    QFrame *line_2;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QPushButton *ConnectToMyChanBtn;
    QLabel *ConNewPassLabel;
    QLabel *NewPassLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *DeleteMyChanBtn;
    QLineEdit *MaxCountUsersEdit;
    QLabel *label_6;
    QLabel *MaxCountUsersLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *SetMCUBtn;
    QLineEdit *ConNewPassEdit;
    QLineEdit *NameChannelEdit;
    QPushButton *ChangeNameBtn;
    QLabel *NameChannelLabel;
    QSpacerItem *verticalSpacer_2;
    QPushButton *ChangePassBtn;
    QLabel *OldPassLabel;
    QLineEdit *OldPassEdit;
    QPushButton *StateChanBtn;

    void setupUi(QWidget *MyChan)
    {
        if (MyChan->objectName().isEmpty())
            MyChan->setObjectName(QString::fromUtf8("MyChan"));
        MyChan->resize(691, 515);
        gridLayout = new QGridLayout(MyChan);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridL = new QGridLayout();
        gridL->setObjectName(QString::fromUtf8("gridL"));
        gridL->setContentsMargins(0, -1, -1, -1);
        NewPassEdit = new QLineEdit(MyChan);
        NewPassEdit->setObjectName(QString::fromUtf8("NewPassEdit"));

        gridL->addWidget(NewPassEdit, 9, 1, 1, 1);

        line_2 = new QFrame(MyChan);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridL->addWidget(line_2, 4, 1, 1, 1);

        line = new QFrame(MyChan);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridL->addWidget(line, 17, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridL->addItem(verticalSpacer, 18, 1, 1, 1);

        ConnectToMyChanBtn = new QPushButton(MyChan);
        ConnectToMyChanBtn->setObjectName(QString::fromUtf8("ConnectToMyChanBtn"));

        gridL->addWidget(ConnectToMyChanBtn, 20, 1, 1, 1);

        ConNewPassLabel = new QLabel(MyChan);
        ConNewPassLabel->setObjectName(QString::fromUtf8("ConNewPassLabel"));

        gridL->addWidget(ConNewPassLabel, 10, 1, 1, 1);

        NewPassLabel = new QLabel(MyChan);
        NewPassLabel->setObjectName(QString::fromUtf8("NewPassLabel"));

        gridL->addWidget(NewPassLabel, 7, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridL->addItem(horizontalSpacer_3, 7, 0, 1, 1);

        DeleteMyChanBtn = new QPushButton(MyChan);
        DeleteMyChanBtn->setObjectName(QString::fromUtf8("DeleteMyChanBtn"));

        gridL->addWidget(DeleteMyChanBtn, 22, 1, 1, 1);

        MaxCountUsersEdit = new QLineEdit(MyChan);
        MaxCountUsersEdit->setObjectName(QString::fromUtf8("MaxCountUsersEdit"));

        gridL->addWidget(MaxCountUsersEdit, 15, 1, 1, 1);

        label_6 = new QLabel(MyChan);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridL->addWidget(label_6, 0, 1, 1, 1);

        MaxCountUsersLabel = new QLabel(MyChan);
        MaxCountUsersLabel->setObjectName(QString::fromUtf8("MaxCountUsersLabel"));

        gridL->addWidget(MaxCountUsersLabel, 14, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridL->addItem(horizontalSpacer_2, 7, 2, 1, 1);

        SetMCUBtn = new QPushButton(MyChan);
        SetMCUBtn->setObjectName(QString::fromUtf8("SetMCUBtn"));

        gridL->addWidget(SetMCUBtn, 16, 1, 1, 1);

        ConNewPassEdit = new QLineEdit(MyChan);
        ConNewPassEdit->setObjectName(QString::fromUtf8("ConNewPassEdit"));

        gridL->addWidget(ConNewPassEdit, 11, 1, 1, 1);

        NameChannelEdit = new QLineEdit(MyChan);
        NameChannelEdit->setObjectName(QString::fromUtf8("NameChannelEdit"));

        gridL->addWidget(NameChannelEdit, 2, 1, 1, 1);

        ChangeNameBtn = new QPushButton(MyChan);
        ChangeNameBtn->setObjectName(QString::fromUtf8("ChangeNameBtn"));

        gridL->addWidget(ChangeNameBtn, 3, 1, 1, 1);

        NameChannelLabel = new QLabel(MyChan);
        NameChannelLabel->setObjectName(QString::fromUtf8("NameChannelLabel"));

        gridL->addWidget(NameChannelLabel, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridL->addItem(verticalSpacer_2, 23, 1, 1, 1);

        ChangePassBtn = new QPushButton(MyChan);
        ChangePassBtn->setObjectName(QString::fromUtf8("ChangePassBtn"));

        gridL->addWidget(ChangePassBtn, 12, 1, 1, 1);

        OldPassLabel = new QLabel(MyChan);
        OldPassLabel->setObjectName(QString::fromUtf8("OldPassLabel"));

        gridL->addWidget(OldPassLabel, 5, 1, 1, 1);

        OldPassEdit = new QLineEdit(MyChan);
        OldPassEdit->setObjectName(QString::fromUtf8("OldPassEdit"));

        gridL->addWidget(OldPassEdit, 6, 1, 1, 1);

        StateChanBtn = new QPushButton(MyChan);
        StateChanBtn->setObjectName(QString::fromUtf8("StateChanBtn"));

        gridL->addWidget(StateChanBtn, 21, 1, 1, 1);

        gridL->setColumnStretch(0, 1);
        gridL->setColumnStretch(1, 5);
        gridL->setColumnStretch(2, 1);

        gridLayout->addLayout(gridL, 0, 0, 1, 1);


        retranslateUi(MyChan);

        QMetaObject::connectSlotsByName(MyChan);
    } // setupUi

    void retranslateUi(QWidget *MyChan)
    {
        MyChan->setWindowTitle(QApplication::translate("MyChan", "Form", nullptr));
        ConnectToMyChanBtn->setText(QApplication::translate("MyChan", "Connect to my channel", nullptr));
        ConNewPassLabel->setText(QApplication::translate("MyChan", "Confirm new password channel:", nullptr));
        NewPassLabel->setText(QApplication::translate("MyChan", "New password channel:", nullptr));
        DeleteMyChanBtn->setText(QApplication::translate("MyChan", "Delete my channel", nullptr));
        label_6->setText(QApplication::translate("MyChan", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">My channel settings</span></p><p align=\"center\"><br/></p></body></html>", nullptr));
        MaxCountUsersLabel->setText(QApplication::translate("MyChan", "Max count users:", nullptr));
        SetMCUBtn->setText(QApplication::translate("MyChan", "Set", nullptr));
        ChangeNameBtn->setText(QApplication::translate("MyChan", "Change", nullptr));
        NameChannelLabel->setText(QApplication::translate("MyChan", "Name channel", nullptr));
        ChangePassBtn->setText(QApplication::translate("MyChan", "Change", nullptr));
        OldPassLabel->setText(QApplication::translate("MyChan", "Old password channel:", nullptr));
        StateChanBtn->setText(QApplication::translate("MyChan", "Start channel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyChan: public Ui_MyChan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCHAN_H
